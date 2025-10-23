
## 通过ffmpeg 拆分、合并音视频
##
##

import ff.ff_info as ff_info
import pathlib
import os
import sys

FFMPEG_BINARY = "ffmpeg.exe"

def get_exe_path():
    """
    返回可执行程序的当前路径。 sys.argv 中保存了可执行程序的全路径
    :return:
    """
    return os.path.split(os.path.realpath(sys.argv[0]))[0]

class FFMPEG_Tools:
    def __init__(self,video_name) -> None:
        self.m_video_name = video_name
        self.m_ff = ff_info.FFMPEG_info(video_name)


    def ff_split_audio(self)->str:
        """拆分音、视频文件

        Returns:
            str: 拆离后的音频文件,音频文件后缀通过解析原文件的音频格式确认,如aac、mp3......
        """
        p = pathlib.Path(self.m_video_name)
        self.m_audio_name = f'{get_exe_path()}\{p.stem}.{self.m_ff.get_audio_codec()}'

        cmd = [FFMPEG_BINARY, "-i", self.m_video_name,'-vn','-y','-acodec copy', self.m_audio_name]

        os.system(' '.join(cmd))

        return self.m_audio_name
    
    def ff_merge(self,in_audio,in_video,out_video):
        """合并音、视频文件

        Args:
            in_audio (_type_): 音频文件
            in_video (_type_): 视频文件
            out_video (_type_): 合并后的文件
        """
        cmd = [FFMPEG_BINARY, '-i', in_video, '-i', in_audio ,'-y', '-c:v copy -c:a copy',out_video]

        os.system(' '.join(cmd))


if __name__ == "__main__":
    # file = r'd:\123\456.mp4'
    # p = pathlib.Path(file) # test.py
    # print(p.suffix)  # .py
    # print(p.stem)	# test
    ff_tool = FFMPEG_Tools(r'E:\aliPan\201.mp4')
    ff_tool.ff_split_audio()