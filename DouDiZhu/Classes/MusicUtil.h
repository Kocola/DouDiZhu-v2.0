/*******************************************************************************
处理音乐的类
若用此类管理音乐，需要：
1. 在开始游戏时（比如splash界面）调用MusicUtil::DoInit()进行初始化
2. 在AppDelegate::applicationDidEnterBackground中调用MusicUtil::PauseBackgroundMusic暂停背景音乐
3. 在AppDelegate::applicationWillEnterForeground中调用MusicUtil::EnterForeground恢复背景音乐
4. 在AppDelegate::~AppDelegate中调用MusicUtil::End结束音乐
5. 在游戏要退出时会自动保存当前的设置。如果想要手动保存设置（比如玩家切换了音乐或音效的开启就想立即保存），
   调用MusicUtil::SaveSettings。
********************************************************************************/

#ifndef __UTIL_MUSICUTIL_H__
#define __UTIL_MUSICUTIL_H__

#include "cocos2d.h"

namespace util {

	class MusicUtil {
	public:
		// 从文件中读取音乐设置
		static void doInit();

		// 背景音乐是否开了
		static bool isBackgroundMusicOn()
		{
			return s_bgMusicOn;
		}

		// 设置背景音乐开关
		static void setBackgroundMusicOn(bool isOn_)
		{
			s_bgMusicOn = isOn_;
		}

		// 特效声音是否开了
		static bool isEffectMusicOn()
		{
			return s_effectMusicOn;
		}

		// 设置特效声音开关
		static void setEffectMusicOn(bool isOn_)
		{
			s_effectMusicOn = isOn_;
		}

		// 播放背景音乐
		// bg_music_name: 背景音乐名字
		// is_loop: 是否循环播放
		static void playBackgroundMusic(const char *musicName_, bool isLoop_);

		// 暂停
		static void pauseBackgroundMusic();

		// 恢复
		static void resumeBackgroundMusic();

		// 停止
		static void stopBackgroundMusic();

		// 播放特效声音，music_name为特效声音名字
		static void playEffectMusic(const char *effectName_);

		// 游戏进入前台
		static void enterForeground();

		// 保存设置到文件
		static void saveSettings();

		// 结束音乐播放（在游戏将要退出时调用）
		static void end();

		// 停止所有声音
		static void stopAll();

		// 设置并保存音效音量
		static void setVolume(float fVolume_);

		// 获得保存的音效音量
		static float getVolume();

		// 设置并保存背景音乐音量
		static void setBgMusicVolume(float fVolume_);

		// 获得保存的背景音乐音量
		static float getBgMusicVolume();

	private:
		static bool		s_bgMusicOn;			// 背景音乐是否开了
		static bool		s_effectMusicOn;		// 特效声音是否开了
		static bool		s_playingBgMusic;				// 是否正在播放背景音乐
		static int		s_musicID;					// 正在播放的背景音乐的id
		static float		s_fEffectVolume;			// 音效音量
		static float		s_fBackgroundMusicVolume;	// 背景音乐音量
		static std::string s_bgMusicName;		// 上次播放的背景音乐的名称
	};

}

#endif // UTIL_MUSICUTIL_H_
