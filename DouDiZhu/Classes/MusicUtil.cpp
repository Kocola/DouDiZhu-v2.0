#include "Musicutil.h"
#include "audio/include/AudioEngine.h"
#include "audio/include/SimpleAudioEngine.h"

using namespace CocosDenshion;

namespace util 
{
	// 保存/读取音乐设置的key
	const char *const kMusicKey = "kMusicKey";
	const char *const kEffectKey = "kEffectKey";
	// 保存/读取音量的key
	const char *const kEffectVolumeKey = "kEffectVolumeKey";
	const char *const kBackgroundMusicVolumeKey = "kBackgroundMusicVolumeKey";

	bool MusicUtil::s_bgMusicOn = true;
	bool MusicUtil::s_effectMusicOn = true;
	bool MusicUtil::s_playingBgMusic = false;
	int MusicUtil::s_musicID = 0;
	float MusicUtil::s_fEffectVolume = 1.0f;
	float MusicUtil::s_fBackgroundMusicVolume = 1.0f;
	std::string MusicUtil::s_bgMusicName = "";

	void MusicUtil::doInit()
	{
		// 读取音乐音效设置
		s_bgMusicOn = cocos2d::UserDefault::getInstance()->getBoolForKey(kMusicKey, false);
		s_effectMusicOn = cocos2d::UserDefault::getInstance()->getBoolForKey(kEffectKey, true);
		// 读取音量
		s_fEffectVolume = cocos2d::UserDefault::getInstance()->getFloatForKey(kEffectVolumeKey, 1.0f);
		s_fBackgroundMusicVolume = cocos2d::UserDefault::getInstance()->getFloatForKey(kBackgroundMusicVolumeKey, 1.0f);
	}

	void MusicUtil::playBackgroundMusic(const char* musicName_, bool isLoop_)
	{
		if (s_playingBgMusic)
		{
			return;
		}
		s_bgMusicName = musicName_;
		if (s_bgMusicOn)
		{
			s_playingBgMusic = true;
			SimpleAudioEngine::getInstance()->playBackgroundMusic(musicName_, true);
		}
	}

	void MusicUtil::pauseBackgroundMusic()
	{
		if (s_bgMusicOn)
		{
			//experimental::AudioEngine::pause(m_nMusicID);
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
	}

	void MusicUtil::resumeBackgroundMusic()
	{
		if (s_playingBgMusic)
		{
			if (s_bgMusicOn)
			{
				//experimental::AudioEngine::resume(m_nMusicID);
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			}
		}
	}

	void MusicUtil::stopBackgroundMusic()
	{
		s_playingBgMusic = false;
		//experimental::AudioEngine::stop(m_nMusicID);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}

	void MusicUtil::playEffectMusic(const char *effect_name)
	{
		//	if (is_effect_music_on_)
		//{
		//experimental::AudioEngine::play2d(effect_name, false, m_fEffectVolume);
		SimpleAudioEngine::getInstance()->playEffect(effect_name);
		//	}
	}

	void MusicUtil::enterForeground()
	{
		if (s_bgMusicOn)
		{
			//experimental::AudioEngine::resume(m_nMusicID);
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}

	void MusicUtil::saveSettings()
	{
		cocos2d::UserDefault::getInstance()->setBoolForKey(kMusicKey, s_bgMusicOn);
		cocos2d::UserDefault::getInstance()->setBoolForKey(kEffectKey, s_effectMusicOn);
		cocos2d::UserDefault::getInstance()->flush();
	}

	void MusicUtil::end()
	{
		saveSettings();  // 游戏结束前保存一次设置，以免忘了游戏中忘记保存了
		//experimental::AudioEngine::end();
		SimpleAudioEngine::getInstance()->end();
	}

	void MusicUtil::stopAll()
	{
		//experimental::AudioEngine::stopAll();
	}

	void MusicUtil::setVolume(float fVolume)
	{
		cocos2d::log("MusicUtil::setVolume %f", fVolume);
		s_fEffectVolume = fVolume;
		SimpleAudioEngine::getInstance()->setEffectsVolume(s_fEffectVolume);
		cocos2d::UserDefault::getInstance()->setFloatForKey(kEffectVolumeKey, s_fEffectVolume);
		cocos2d::UserDefault::getInstance()->flush();
	}

	float MusicUtil::getVolume()
	{
		return s_fEffectVolume;
	}

	void MusicUtil::setBgMusicVolume(float fVolume)
	{
		cocos2d::log("MusicUtil::setBgMusicVolume %f", fVolume);
		s_fBackgroundMusicVolume = fVolume;
		//experimental::AudioEngine::setVolume(m_nMusicID, m_fBackgroundMusicVolume);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(s_fBackgroundMusicVolume);
		cocos2d::UserDefault::getInstance()->setFloatForKey(
			kBackgroundMusicVolumeKey, s_fBackgroundMusicVolume);
		cocos2d::UserDefault::getInstance()->flush();
	}

	float MusicUtil::getBgMusicVolume()
	{
		return s_fBackgroundMusicVolume;
	}
}
