
import libfcdetec
import ff.ff_read as ff_read
import ff.ff_write as ff_write
import ff.ff_info as ff_info
import ff.ff_tools as ff_tools
import os
import sys
import pathlib

def get_exe_path():
    """
    返回可执行程序的当前路径。 sys.argv 中保存了可执行程序的全路径
    :return:
    """
    return os.path.split(os.path.realpath(sys.argv[0]))[0]


def init_libfc():
    return libfcdetec.libfcdetec_init('')

class video_fs:
    def __init__(self,video_name) -> None:
        self.m_total_frame = 0
        self.m_video_name = video_name

        p = pathlib.Path(self.m_video_name)

        self.m_video = f'{get_exe_path()}\{p.stem}_video{p.suffix}'

        info = ff_info.FFMPEG_info(video_name)

        self.m_fps = info.get_fps()
        self.m_width = info.get_width() 
        self.m_height = info.get_height()
        self.m_duration = info.get_duration()
        self.m_total_frame = info.get_total_frame()

    def get_total_frame(self):
        return self.m_total_frame

    def video_fs(self,output_video,callback_func):
        """通过ff_read解码,将bgr数据扔给c++处理分析、马赛克处理，然后写入ff_write.
        """

        # 1、提取音频文件
        ff_tool = ff_tools.FFMPEG_Tools(self.m_video_name)
        audio_name = ff_tool.ff_split_audio()

        # 2、对视频进行处理
        f_reader = ff_read.FFMPEG_VideoReader(self.m_video_name,pixel_format = 'bgr24',decode_file = False)
        f_video_writer = ff_write.FFMPEG_VideoWriter(self.m_video,(self.m_width,self.m_height),self.m_fps,pixel_format = 'bgr24')
        current_frame = 1
        f_start_time = libfcdetec.localtime()
        while current_frame < self.m_total_frame:
            print(f'\r 进度 {libfcdetec.localtime()}/{f_start_time} -- {current_frame}/{self.m_total_frame}',end='')
            if callback_func:
                callback_func(current_frame,self.m_total_frame)
            frame = f_reader.read_frame()
            # 对输入的数据进行人脸检测，并马赛克处理
            libfcdetec.libfcdetec_fcdection_Mat(frame.shape[0],frame.shape[1],1,frame.__array_interface__['data'][0])

            # 修改后的数据重新写入视频文件中
            f_video_writer.write_frame(frame)

            current_frame += 1
        
        f_video_writer.close()
        
        # 3、音视频合并
        ff_tool.ff_merge(audio_name,self.m_video,output_video)

        print('--end videoMosaic--')
    

if __name__ == "__main__":
    libfcdetec.libfcdetec_init('')
    fs = video_fs(r'd:\143.mp4')
    out_put = f'{get_exe_path()}\output.mp4'
    fs.video_fs(out_put)



   