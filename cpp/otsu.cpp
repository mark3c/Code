// Multi OTSU
#include <iostream>
#include <numeric>
#include <time.h>
#include <vector>

#include <mutex>
#include <omp.h>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "index.h"

std::vector<float> mat2vec(cv::Mat mat) {
    std::vector<float> array;
    if (mat.isContinuous()) {
        // array.assign((float*)mat.datastart, (float*)mat.dataend); // <- has
        // problems for sub-matrix like mat = big_mat.row(i)
        array.assign((float *)mat.data,
                     (float *)mat.data + mat.total() * mat.channels());
    } else {
        for (int i = 0; i < mat.rows; ++i) {
            array.insert(array.end(), mat.ptr<float>(i),
                         mat.ptr<float>(i) + mat.cols * mat.channels());
        }
    }
    return array;
}

std::vector<int> find_threshold(const int _level, const int L,
                                const std::vector<std::vector<float>> &tableh) {
    float fn_min = 0.;
    std::vector<int> idx(_level + 1, 0);
    std::vector<int> thresh;
    std::vector<std::vector<float>> ans(L, std::vector<float>(L, 0));
    std::mutex mtx;

    std::function<void(int, int, float)> loop = [&](int t0, int level,
                                                    float fn) {
        idx[level] = t0;

        if (level == 0) {
            fn += tableh[t0][L - 1];
            mtx.lock();
            if (fn > fn_min) {
                thresh = idx;
                fn_min = fn;
            }
            mtx.unlock();
            return;
        }

        for (int i = t0; i < L - level; ++i) {
            loop(i + 1, level - 1, fn + tableh[t0][i]);
        }
        return;
    };

    // #pragma omp parallel for
    for (int i = 0; i < L - _level; ++i) {
        loop(i + 1, _level - 1, tableh[0][i]);
    }

    return thresh;
}

int otsu() {
    std::string img_path = IMGPATH_CAT;

    cv::Mat mat = cv::imread(img_path, cv::IMREAD_COLOR);
    cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);

    cv::Mat blur;
    cv::GaussianBlur(mat, blur, {5, 5}, 0);

    int HIST_SIZE = 256;

    cv::Mat hist;
    cv::calcHist(std::vector<cv::Mat>{blur}, std::vector<int>{0}, cv::Mat(),
                 hist, std::vector<int>{HIST_SIZE}, std::vector<float>{0, 256});

    auto histnorm = mat2vec(hist);
    auto x = *std::max_element(histnorm.begin(), histnorm.end());
    std::for_each(histnorm.begin(), histnorm.end(),
                  [x](auto val) { return val / x; });

    std::vector<float> p, s;
    p.reserve(HIST_SIZE);
    s.reserve(HIST_SIZE);
    std::partial_sum(histnorm.begin(), histnorm.end(), back_inserter(p));
    std::partial_sum(histnorm.begin(), histnorm.end(), back_inserter(s),
                     [](auto pre, auto val) {
                         static int i = 0;
                         return pre + val * (i++);
                     });

    std::vector<std::vector<float>> tableh(HIST_SIZE,
                                           std::vector<float>(HIST_SIZE));
    for (int i = 0; i < HIST_SIZE; ++i) {
        for (int j = 0; j < HIST_SIZE; ++j) {
            if (i != 0 && p[j] != p[i - 1]) {
                tableh[i][j] =
                    (s[j] - s[i - 1]) * (s[j] - s[i - 1]) / (p[j] - p[i - 1]);
            } else if (p[j] != 0) {
                tableh[i][j] = s[j] * s[j] / p[j];
            }
        }
    }

    int level = 2;
    auto start = clock();
    std::vector<int> thresh = find_threshold(level, HIST_SIZE, tableh);
    auto end = clock();

    for (auto t : thresh)
        std::cout << t << " ";
    std::cout << std::endl;

    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar *lookp = lookUpTable.ptr();
    for (int i = 0; i < 256; ++i)
        for (uchar t : thresh) {
            if (i > t) {
                lookp[i] = t;
                break;
            }
        }

    cv::LUT(blur, lookUpTable, blur);

    // blur.forEach<uint8_t>([&thresh](uint8_t &val, const int *pos) {
    //     for (uint8_t t : thresh) {
    //         if (val > t) {
    //             val = t;
    //             break;
    //         }
    //     }
    // });
    cv::namedWindow("cat", cv::WINDOW_NORMAL);
    cv::imshow("cat", blur);
    cv::waitKey(0);
    cv::destroyAllWindows();
    std::cout << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}
