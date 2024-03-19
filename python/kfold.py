from torch.utils.data import DataLoader, ConcatDataset, SubsetRandomSampler
from sklearn.model_selection import KFold

def trainKfold(params, kwargs):
    kflods = 10
    dataloaders = {}

    dataset_train = PolerDataset(params.dataset_path, 'train')
    dataset_val = PolerDataset(params.dataset_path, 'val')
    dataset = ConcatDataset([dataset_train, dataset_val])

    kfold = KFold(n_splits=kflods, shuffle=True)
    kfold = kfold.split(np.arange(len(dataset)))
    for fold, (train_ids, val_ids) in enumerate(kfold):
        dataloaders['train'] = DataLoader(
            dataset,
            batch_size=params.train_batch,
            sampler=SubsetRandomSampler(train_ids.tolist()),
            num_workers=2, 
            pin_memory=True, 
            drop_last=True
        )
        dataloaders['val'] = DataLoader(
            dataset,
            batch_size=params.train_batch,
            sampler=SubsetRandomSampler(val_ids.tolist()),
            num_workers=2,
            pin_memory=True
        )

        trainer = getTrainer(params, kwargs)
        res = trainer.train(dataloaders=dataloaders)
        for k, v in res.items():
            result[k] += v
    for k in result:
        result[k] /= kflods

