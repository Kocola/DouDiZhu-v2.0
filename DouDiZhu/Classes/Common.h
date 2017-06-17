#ifndef					__COMMON_H__
#define					__COMMON_H__

#include <string>

const char* const pressBtnMusic = "music/btnpress.mp3";

const char DIALOG_BG_IMAGE[] = "image/lobby/dialog_bg.png";
const char DIALOG_TOP_BG_IMAGE[] = "image/lobby/dialog_bgTop.png";
const char DIALOG_BTN[] = "image/lobby/dialog_btn.png";
const char SET_DIALOG_EFFECT[] = "image/lobby/set/setting-effect.png";	//设置音效
const char SET_DIALOG_MUSIC[] = "image/lobby/set/setting-music.png";
const char SET_DIALOG_PROGRESS[] = "image/lobby/set/setting-progress.png";
const char SET_DIALOG_SLIDER[] = "image/lobby/set/setting-slider.png";
const char SET_DIALOG_TRACK[] = "image/lobby/set/setting-track.png";
const char DIALOG_CLOSE_BTN[] = "image/lobby/close_btn.png";
const char DIALOG_MIDDLE_BG_IMAGE[] = "image/lobby/dialog-middleBg.png";
const char START_DIALOG_ICON[] = "image/lobby/start_game.png";

const char GAME_SCENE_BG[] = "image/game/gamescene_bg.png";
const char GAME_SCENE_BORDER[] = "image/game/gamescene_border.png";
const char GAME_SCENE_CORNER[] = "image/game/gamescene_ corner.png";
const char GAME_SCENE_LEFT_LEAF[] = "image/game/left_leafi.png";
const char GAME_SCENE_RIGHT_LEAF[] = "image/game/right_leaf.png";

const char HEAD_IMAGES[] = "image/game/headimage/head_image.png";
const char HEAD_IMAGE_LIST[] = "image/game/headimage/head_image.plist";
const char HEAD_BOX[] = "image/game/headimage/head_box.png";
const char NO_HEAD[] = "image/game/headimage/no_head.png";

const char gameStateReady[] = "image/game/ready.png";
const char gameStateReadyBtn[] = "image/game/btn_start.png";

const char LOBBY_BG[] = "image/lobby/lobby_bg.png";
const char LOBBY_TOP_BG[] = "image/lobby/lobby_top_bg.png";
const char LOBBY_HEAD_BOX[] = "image/lobby/head_box.png";
const char LOBBY_HEAD[] = "image/lobby/head.png";
const char LOBBY_SLOGAN_BG[] = "image/lobby/slogan_bg.png";
const char LOBBY_SLOGAN[] = "image/lobby/slogan.png";
const char LOBBY_SETTING[] = "image/lobby/setting.png";
const char LOBBY_RULE[] = "image/lobby/rule.png";
const char LOBBY_FEEDBACK[] = "image/lobby/feedback.png";
const char LOBBY_BTN_LINE[] = "image/lobby/lobby_btn_line.png";	//按钮之间的分割线
const char LOBBY_MARQUEE_RIGHT[] = "image/lobby/lobby_marquee_right.png";
const char LOBBY_MARQUEE_LEFT[] = "image/lobby/lobby_marquee_left.png";
const char LOBBY_BOTTOM_BG[] = "image/lobby/lobby_bottom_bg.png";
const char LOBBY_SHARE[] = "image/lobby/share.png";
const char LOBBY_ACTIVITY[] = "image/lobby/activity.png";
const char LOBBY_RECORD[] = "image/lobby/record.png";
const char START_GAME[] = "image/lobby/start_game.png";

const char NOCALLBTN[] = "image/game/calllandlord/btn_nocall.png";
const char CALLONEBTN[] = "image/game/calllandlord/btn_one.png";
const char CALLTWOBTN[] = "image/game/calllandlord/btn_two.png";
const char CALLTHREEBTN[] = "image/game/calllandlord/btn_three.png";

const char HINT_BTN[] = "image/game/btn_hint.png";
const char HINT_DISABLE_BTN[] = "image/game/btn_hint_disabled.png";
const char OUTPOKER_BTN[] = "image/game/btn_out.png";
const char OUTPOKER_DISABLE_BTN[] = "image/game/btn_out_disabled.png";
const char PASS_BTN[] = "image/game/btn_pass.png";
const char PASS_DISABLE_BTN[] = "image/game/btn_pass_disabled.png";

const char headLandlordLeft[] = "landlord_boy_left.png";
const char headLandlordRight[] = "landlord_boy_right.png";
const char headFarmerLeft[] = "farmer_boy_left.png";
const char headFarmerRight[] = "farmer_boy_right.png";

const char NOCALLSTATE[] = "flagcall_0.png";
const char CALLONESTATE[] = "flagcall_1.png";
const char CALLTWOSTATE[] = "flagcall_2.png";
const char CALLTHREESTATE[] = "flagcall_3.png";

const char PASS_IMAGE[] = "image/game/pass.png";

const int COMMON_DIALOG_ZORDER = 1;

const int SINGLE_TYPE_CARD_NUM = 13;

const int DIALOG_WIDTH = 720;
const int DIALOG_HEIGHT = 480;

const std::string CREATE_HEADIMAGE_LAYER = "createHeadImageLayer";		//创建头像层
const std::string DESTROY_HEADIMAGE_LAYER = "destroyHeadImageLayer";	//销毁头像层
const std::string CREATE_READY_LAYER = "createReadyLayer";		//创建准备层
const std::string DESTROY_READY_LAYER = "destroyReadyLayer";	//销毁准备层
const std::string CREATE_POKER_LAYER = "createPokerLayer";			//创建扑克层
const std::string DESTROY_POKER_LAYER = "destroyPokerLayer";	//销毁扑克层
const std::string CREATE_CALL_LANDLORD_LAYER = "createCallLandlordLayer";	//创建叫地主层
const std::string DESTROY_CALL_LANDLORD_LAYER = "destroyCallLandlordLayer";	//销毁叫地主层
const std::string CREATE_OVER_LAYER = "createOverLayer";	//创建结束层
const std::string DESTROY_OVER_LAYER = "destroyOverLayer";	//销毁结束层

const std::string UPDATE_GAME_STATE = "updateGameState";		//更新游戏状态
const std::string UPDATE_CALL_LANDLORD_INDEX = "updateCallLandlordIndex";	//更新叫地主顺序
const std::string DISPLAY_CALL_LANDLORD_BTN = "displayCallLandlordBtn";			//显示手动玩家叫地主按钮

//玩家叫分回调
const std::string COMPUTER_ONE_NOCALL = "computerOneNoCall";
const std::string COMPUTER_ONE_CALLONE = "computerOneCallOne";
const std::string COMPUTER_ONE_CALLTWO = "computerOneCallTwo";
const std::string COMPUTER_ONE_CALLTHREE = "computerOneCallThree";

const std::string COMPUTER_TWO_NOCALL = "computerTwoNoCall";
const std::string COMPUTER_TWO_CALLONE = "computerTwoCallOne";
const std::string COMPUTER_TWO_CALLTWO = "computerTwoCallTwo";
const std::string COMPUTER_TWO_CALLTHREE = "computerTwoCallThree";

//显示玩家叫分回调
const std::string DISPLAY_COMPUTE_ONE_CALLLANDLORD_STATE = "displayComputerOneCallState";
const std::string DISPLAY_COMPUTE_TWO_CALLLANDLORD_STATE = "displayComputerTwoCallState";

const std::string GAME_CONTROLLER_RUN = "gameControllerRun";	//游戏控制器运行
const std::string DISPLAY_HOLDER_POKERS = "displayHolderPokers";	//显示手动玩家（自己）手中的牌
const std::string DISPLAY_LANDLORD_POKERS = "displayLandlordPokers";	//显示预留给地主的牌
const std::string UPDATE_HOLDER_HEADIMAGE = "updateHolderHeadImage";	//更新手动玩家头像为地主
const std::string UPDATE_COMPUTERONE_HEADIMAHE = "updateComputerOneHeadImage";	//更新电脑玩家1头像为地主
const std::string UPDATE_COMPUTERTWO_HEADIMAGE = "updateComputerTwoHeadImage";	//更新电脑玩家2头像为地主

const std::string POKER_IMAGES = "image/game/poker/Joker.png";
const std::string POKER_IMAGE_LIST = "image/game/poker/Joker.plist";
const std::string CALL_LANDLORD_IMAGES = "image/game/calllandlord/call_landlord_state.png";
const std::string CALL_LANDLORD_IMAGE_LIST = "image/game/calllandlord/call_landlord_state.plist";

const std::string COUNTDOWN_IMAGES = "image/game/clock/clock.png";
const std::string COUNTDOWN_IMAGE_LIST = "image/game/clock/clock.plist";
const std::string COUNTDOWN_NUMS = "image/game/clock/clock_num.png";

const std::string PASS_HINT = "image/game/passhint.png";	//提示没有打得过上家的牌图片

const std::string DESTROY_LAST_HOLDER_OUTPOKERS = "destroyLastHolderOutPokers";
const std::string DISPLAY_HOLDER_OUTPOKERS = "displayHolderOutPokers";//显示手动玩家要出的牌
const std::string DESTROY_LAST_COMPUTER_ONE_OUTPOKERS = "destroyLastComputerOneOutPokers";
const std::string DISPLAY_COMPUTER_ONE_OUTPOKERS = "displayComputerOneOutPokers";
const std::string DESTROY_LAST_COMPUTER_TWO_OUTPOKERS = "destroyLastComputerTwoOutPokers";
const std::string DISPLAY_COMPUTER_TWO_OUTPOKERS = "displayComputerTwoOutPokers";

const std::string ADD_POKER_IN_HOLDER_POKERSWAITFOROUT = "addPokerInHolderPokersWaitForOut";	//在手动玩家准备出的牌中添加牌
const std::string DELETE_POKER_IN_HOLDER_POKERSWAITFOROUT = "deletePokerInHolderPokersWaitForOut";	//在手动玩家准备出的牌中删除牌

const std::string UPDATE_OUT_ORDER = "updateOutOrder";	//更新出牌顺序
const std::string DISPLAY_HOLDER_OUTPOKERS_BTNS = "displayHolderOutPokersBtns";	//显示手动玩家出牌相关按钮
//const std::string IS_HOLDER_POKERS_CAN_OUT = "isHolderPokersCanOut";	//手动玩家选择的牌是否可以出
const std::string OUTPOKERS_BTN_ENABLED = "outPokersBtnEnabled";	//出牌按钮可以按下
const std::string OUTPOKERS_BTN_DISABLED = "outPokersBtnDisabled";	//出牌按钮不可按
const std::string HINT_BTN_ENABLED = "hintBtnEnabled";		//提示按钮可按
const std::string HOLDER_OUTPOKERS = "holderOutPokers";		//手动玩家出牌
const std::string UPDATE_LAST_OUTPOKERS = "updateLastOutPokers";	//更新上一手牌
const std::string CLICK_HINT_BTN = "clickHintBtn";	//点击提示按钮
const std::string MAKE_HINT_POKERS_SELECTED = "makeHintPokersSelected";	//令提示按钮被选中（表示待出）
const std::string SHOW_PASSHINT = "showPassHint";	

// const std::string START_COUNTDOWN = "startCountDown";		//开始倒计时
// const std::string STOP_COUNTDOWN = "stopCountDown";	//停止倒计时
const std::string HOLDER_START_COUNTDOWN = "holderStartCountDown";	//手动玩家计时器开始计时
const std::string HOLDER_STOP_COUNTDOWN = "holderStopCountDown";	//手动玩家计时器停止计时
const std::string COMPUTER_ONE_START_COUNTDOWN = "computerOneStartCountDown";	//电脑玩家1计时器开始计时
const std::string COMPUTER_TWO_START_COUNTDOWN = "computerTwoStartCountDown";	//电脑玩家2计时器开始计时

const std::string LOST_ANIMATION_IMAGES = "image/game/animation/lost/lost.png";
const std::string LOST_ANIMATION_IMAGE_LIST = "image/game/animation/lost/lost.plist";
const std::string WIN_ANIMATION_IMAGES = "image/game/animation/win/win.png";
const std::string WIN_ANIMATION_IMAGE_LIST = "image/game/animation/win/win.plist";

const std::string RUN_WIN_ANIMATION = "runWinAnimation";	//运行胜利动画
const std::string RUN_LOST_ANIMATION = "runLostAnimation";	//运行失败动画
const std::string RETURN_TO_LOBBY = "returnToLobby";	//返回游戏大厅

#endif