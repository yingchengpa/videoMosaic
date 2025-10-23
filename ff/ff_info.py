
import ffmpeg


def ratestr2int(rate:str):
    """ 123/25 格式

    Args:
        rate (str): _description_
    """
    str_split = rate.split(r'/')

    return int(str_split[0]),int(str_split[1])

class FFMPEG_info:
    """通过ffmpeg probe 获取文件信息
    """
    def __init__(self,video_name) -> None:
        info = ffmpeg.probe(video_name)

        self.video_s = next(c for c in info['streams'] if c['codec_type'] == 'video')
        self.audio_s = next(c for c in info['streams'] if c['codec_type'] == 'audio')

    def get_width(self):
        return self.video_s['width']
    
    def get_height(self):
        return self.video_s['height']
    
    def get_fps(self):
         ## 使用平均帧率
        num, total_frame = ratestr2int(self.video_s['avg_frame_rate']) 
        fps = round(num/total_frame) # 四舍五入取整 
        return fps
    
    def get_duration(self)->int:
        """duration:int(s),时长

        Returns:
            int: _description_
        """
        return round(float(self.video_s['duration']))
    
    def get_video_codec(self)->str:
        return self.video_s['codec_name']
    
    def get_total_frame(self)->int:
        """视频总帧数

        Returns:
            int: _description_
        """
        total_frame = int(self.video_s['nb_frames'])
        return total_frame
    
    def get_audio_codec(self)->str:
        """音频编码格式

        Returns:
            str: _description_
        """
        return self.audio_s['codec_name']

if __name__ == "__main__":
    ff = FFMPEG_info(r'E:\aliPan\201.mp4')
    print(ff.video_s)
