#ifndef _AUTOTRACKER_H_
#define _AUTOTRACKER_H_

void send_save_data_to_computer_using_settings(Settings *settings);
void send_gold_balloon_data_to_computer(u16 balloonFlag, u8 worldId, u8 levelId);
void send_map_warp_data_from_warp();
void send_map_warp_data_from_loop(u8 mapIdToWarpTo, s32 updateRate);

#endif
