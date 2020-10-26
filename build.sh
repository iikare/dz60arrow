#!/bin/sh

cp -r keyboards/ qmk_firmware
cd qmk_firmware
make dz60:dz60arrow
cp dz60_dz60arrow.hex ..
cd ..

