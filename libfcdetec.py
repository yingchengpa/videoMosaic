# -*- coding: UTF-8 -*-

############################################################################
#
#   Copyright (c) 2020  Bresee, Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License"
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
############################################################################

### 通过libfcdetec库， 实现视频的人脸检测和马赛克处理

### 中文格式请注意： dll 和 py 之间通过json参数传递时，中文采用utf8格式 ；
###               dll 和 py 之间通过c_char_p直接传递时，中文采用gbk格式



# 设置dll的加载路径
import sys

from ctypes import *
import json
import datetime as dt


def localtime():
    """返回local的时间格式 2020-10-10 12:00:00"""
    return (dt.datetime.now()).strftime('%T')


libfc = cdll.LoadLibrary('./bin/libfcdetec.dll')

def libfcdetec_init(dic) -> int:
    b_argDic = json.dumps(dic).encode('utf8')
    libfc.libfcdetec_init.restype = c_int32
    libfc.libfcdetec_init.argtypes = (c_char_p,)

    return libfc.libfcdetec_init(b_argDic)


def libfcdetec_fcdection_img(file_name) -> str:

    b_file_name = file_name.encode('gbk')
    libfc.libfcdetec_fcdection_img.restype = c_char_p
    libfc.libfcdetec_fcdection_img.argtypes = (c_void_p,)

    return bytes.decode(libfc.libfcdetec_fcdection_img(b_file_name))


def libfcdetec_fcdection_Mat(rows:int, cols:int, type:int, data):

    libfc.libfcdetec_fcdection_Mat.restype = c_char_p
    libfc.libfcdetec_fcdection_Mat.argtypes = (c_int32,c_int32,c_int32,c_void_p)

    return bytes.decode(libfc.libfcdetec_fcdection_Mat(rows,cols,type,data))

if __name__ == "__main__":
    pass


        