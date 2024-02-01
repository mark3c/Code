# using ant to complie flex project

## build.xml

```xml
<?xml version="1.0" encoding="utf-8"?>
<project name="xxx" default="build" basedir=".">

    <property name="FLEX_HOME" value="" />
    <property name="FLEX_UNIT" value="" />
    <property name="target" value="XXX" />
    <property name="Debugger" value="" />

    <taskdef resource="flexTasks.tasks" classpath="${FLEX_HOME}/ant/lib/flexTasks.jar" />
    <taskdef resource="flexUnitTasks.tasks" classpath="${FLEX_UNIT}/flexUnitTasks*.jar">

    <target name="build" depends="compile.asdoc" />

    <target name="check">
        <delete dir="${basedir}/build" />
        <mkdir dir="${basedir}/build" />
    </target>

    <target name="compile.mxmlc" depends="check">
        <mxmlc file="${basedir}/src/**/Main.mxml" output="${basedir}/build/${target}.swf"
            fork="true" maxmemory="1024m" configname="air">

            <namespace uri="http://www.adobe.com/2009/foo" manifest="${basedir}/frameworks/projects/framework/manifest.xml" />

            <source-path path-element="${basedir}/src" />
            <include-sources dir="${basedir}/src" includes="**/*" />

            <library-path dir="${basedir}/libs" includes="*" append="true" />
        </mxmlc>

    </target>

    <target name="compile.compc" depends="check">
        <compc output="${basedir}/build/${target}.swc"
            fork="true" maxmemory="1024m" failonerror="true"> 

            <source-path path-element="${basedir}/src" />
            <include-sources dir="${basedir}/src" includes="**/*.as" />

            <library-path dir="${basedir}/libs" includes="*" append="true" />
            <external-library-path dir="${FLEX_HOME}/frameworks/libs" includes="**/*.swc"> 
        </compc>
     
    </target>

    <target name="compile.asdoc" depends="compile.compc">
        <asdoc output="${basedir}/build/docs"
            lenient="true" failonerror="true" 
            keep-xml="true" skip-xsl="true" fork="true">

            <source-path path-element="${basedir}/src" />
            <doc-sources path-element="${basedir}/src" />
        </asdoc>

        <zip destfile="${basedir}/build/${target}.swc" update="true">
            <zipfileset dir="${basedir}/build/docs/tempdita" prefix="docs">
                <include name="*.*"/>
                <exclude name="ASDoc_Config.xml" />
                <exclude name="overviews.xml" />
            </zipfileset>
        </zip>
    </target>

    <target name="pack">
        <copy file="${basedir}/src/swf2png-app.xml" todir="${DEPLOY.dir}" overwrite="true"/>
        <replace file="${DEPLOY.dir}/swf2png-app.xml" token="[This value will be overwritten by Flash Builder in the output app.xml]" value="swf2png.swf"/>
        <exec executable="${FLEX_HOME}/bin/adt.bat" failonerror="true">
            <arg line="-package"/>
            <arg line="-storetype pkcs12"/>
            <arg line="-keystore ${basedir}/certificate.p12"/>
            <arg line="-storepass <password>"/>
            <arg line="${DEPLOY.dir}/swf2png.air"/>
            <arg line="${DEPLOY.dir}/swf2png-app.xml"/>
            <arg line="-C ${DEPLOY.dir} swf2png.swf"/>
        </exec>
    </target>
 
</project>
```

> [Example : Using ANT with COMPC to compile SWCs](https://www.mikechambers.com/blog/2006/05/19/example-using-ant-with-compc-to-compile-swcs/)
> [Compiling Adobe Flex with Ant](https://joshuarogers.net/articles/2012-05/compiling-adobe-flex-ant/)
> [Flex Library ANT 编译](https://blog.csdn.net/ganxunzou/article/details/51224557)
> [Flex使用Ant编译介绍](http://huang-x-h.github.io/2014/03/22/flex-compile-ant/)
> [using-ant-to-build-flash](https://github.com/honzabrecka/using-ant-to-build-flash/blob/master/README.md)
