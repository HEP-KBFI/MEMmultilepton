#!/bin/bash

cp config_template.cfg ../test/config.cfg
cd ..
sed -i s,MEMDIR,${PWD},g test/config.cfg
cd -
