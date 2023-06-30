# export DISPLAY=localhost:0.0

import csv
import struct
import numpy as np
import matplotlib.pyplot as plt

SIDE_CNT      = 6
AS7341_CH_CNT = 10

time_stamp    = []
Seq_num       = []
Bat_v         = []
ACCX          = []
ACCY          = []
ACCZ          = []
GYROX         = []
GYROY         = []
GYROZ         = []
Internal_Temp = []

AS7341_1_CH1  = []
AS7341_1_CH2  = []
AS7341_1_CH3  = []
AS7341_1_CH4  = []
AS7341_1_CH5  = []
AS7341_1_CH6  = []
AS7341_1_CH7  = []
AS7341_1_CH8  = []
AS7341_1_CH9  = []
AS7341_1_CH10 = []

AS7341_2_CH1  = []
AS7341_2_CH2  = []
AS7341_2_CH3  = []
AS7341_2_CH4  = []
AS7341_2_CH5  = []
AS7341_2_CH6  = []
AS7341_2_CH7  = []
AS7341_2_CH8  = []
AS7341_2_CH9  = []
AS7341_2_CH10 = []

AS7341_3_CH1  = []
AS7341_3_CH2  = []
AS7341_3_CH3  = []
AS7341_3_CH4  = []
AS7341_3_CH5  = []
AS7341_3_CH6  = []
AS7341_3_CH7  = []
AS7341_3_CH8  = []
AS7341_3_CH9  = []
AS7341_3_CH10 = []

AS7341_4_CH1  = []
AS7341_4_CH2  = []
AS7341_4_CH3  = []
AS7341_4_CH4  = []
AS7341_4_CH5  = []
AS7341_4_CH6  = []
AS7341_4_CH7  = []
AS7341_4_CH8  = []
AS7341_4_CH9  = []
AS7341_4_CH10 = []

AS7341_5_CH1  = []
AS7341_5_CH2  = []
AS7341_5_CH3  = []
AS7341_5_CH4  = []
AS7341_5_CH5  = []
AS7341_5_CH6  = []
AS7341_5_CH7  = []
AS7341_5_CH8  = []
AS7341_5_CH9  = []
AS7341_5_CH10 = []

AS7341_6_CH1  = []
AS7341_6_CH2  = []
AS7341_6_CH3  = []
AS7341_6_CH4  = []
AS7341_6_CH5  = []
AS7341_6_CH6  = []
AS7341_6_CH7  = []
AS7341_6_CH8  = []
AS7341_6_CH9  = []
AS7341_6_CH10 = []

SIDE_1_TEMP   = []
SIDE_2_TEMP   = []
SIDE_3_TEMP   = []
SIDE_4_TEMP   = []
SIDE_5_TEMP   = []
SIDE_6_TEMP   = []

SIDE_1_HUMD   = []
SIDE_2_HUMD   = []
SIDE_3_HUMD   = []
SIDE_4_HUMD   = []
SIDE_5_HUMD   = []
SIDE_6_HUMD   = []


# AS7341        = [[]]

def process_file(line_in):
	frame_Byte_cnt  = len(line_in)
	frame_data_cnt  = int(frame_Byte_cnt/4)
	frame_byte_temp = []
	
	for i in np.arange(frame_data_cnt):
		str_temp = line_in[i * 4: i * 4 + 4]
		byte_temp = []
		for ii in str_temp:
			byte_temp.append(int(ii))
		# frame_byte_temp.append(byte_temp)
		byte_temp = bytes(byte_temp)
		frame_byte_temp.append(byte_temp)

	time_stamp.append(int.from_bytes(frame_byte_temp[0], "little"))
	Seq_num.append(int.from_bytes(frame_byte_temp[1], "little"))
	Bat_v.append(int.from_bytes(frame_byte_temp[2], "little"))
	ACCX.append(struct.unpack('f', frame_byte_temp[3]))
	ACCY.append(struct.unpack('f', frame_byte_temp[4]))
	ACCZ.append(struct.unpack('f', frame_byte_temp[5]))
	GYROX.append(struct.unpack('f', frame_byte_temp[6]))
	GYROY.append(struct.unpack('f', frame_byte_temp[7]))
	GYROZ.append(struct.unpack('f', frame_byte_temp[8]))

	Internal_Temp.append(struct.unpack('f', frame_byte_temp[9]))

	AS7341_1_CH1.append(int.from_bytes(frame_byte_temp[10], "little"))
	AS7341_1_CH2.append(int.from_bytes(frame_byte_temp[11], "little"))
	AS7341_1_CH3.append(int.from_bytes(frame_byte_temp[12], "little"))
	AS7341_1_CH4.append(int.from_bytes(frame_byte_temp[13], "little"))
	AS7341_1_CH5.append(int.from_bytes(frame_byte_temp[14], "little"))
	AS7341_1_CH6.append(int.from_bytes(frame_byte_temp[15], "little"))
	AS7341_1_CH7.append(int.from_bytes(frame_byte_temp[16], "little"))
	AS7341_1_CH8.append(int.from_bytes(frame_byte_temp[17], "little"))
	AS7341_1_CH9.append(int.from_bytes(frame_byte_temp[18], "little"))
	AS7341_1_CH10.append(int.from_bytes(frame_byte_temp[19], "little"))

	AS7341_2_CH1.append(int.from_bytes(frame_byte_temp[20], "little"))
	AS7341_2_CH2.append(int.from_bytes(frame_byte_temp[21], "little"))
	AS7341_2_CH3.append(int.from_bytes(frame_byte_temp[22], "little"))
	AS7341_2_CH4.append(int.from_bytes(frame_byte_temp[23], "little"))
	AS7341_2_CH5.append(int.from_bytes(frame_byte_temp[24], "little"))
	AS7341_2_CH6.append(int.from_bytes(frame_byte_temp[25], "little"))
	AS7341_2_CH7.append(int.from_bytes(frame_byte_temp[26], "little"))
	AS7341_2_CH8.append(int.from_bytes(frame_byte_temp[27], "little"))
	AS7341_2_CH9.append(int.from_bytes(frame_byte_temp[28], "little"))
	AS7341_2_CH10.append(int.from_bytes(frame_byte_temp[29], "little"))

	AS7341_3_CH1.append(int.from_bytes(frame_byte_temp[30], "little"))
	AS7341_3_CH2.append(int.from_bytes(frame_byte_temp[31], "little"))
	AS7341_3_CH3.append(int.from_bytes(frame_byte_temp[32], "little"))
	AS7341_3_CH4.append(int.from_bytes(frame_byte_temp[33], "little"))
	AS7341_3_CH5.append(int.from_bytes(frame_byte_temp[34], "little"))
	AS7341_3_CH6.append(int.from_bytes(frame_byte_temp[35], "little"))
	AS7341_3_CH7.append(int.from_bytes(frame_byte_temp[36], "little"))
	AS7341_3_CH8.append(int.from_bytes(frame_byte_temp[37], "little"))
	AS7341_3_CH9.append(int.from_bytes(frame_byte_temp[38], "little"))
	AS7341_3_CH10.append(int.from_bytes(frame_byte_temp[39], "little"))

	AS7341_4_CH1.append(int.from_bytes(frame_byte_temp[40], "little"))
	AS7341_4_CH2.append(int.from_bytes(frame_byte_temp[41], "little"))
	AS7341_4_CH3.append(int.from_bytes(frame_byte_temp[42], "little"))
	AS7341_4_CH4.append(int.from_bytes(frame_byte_temp[43], "little"))
	AS7341_4_CH5.append(int.from_bytes(frame_byte_temp[44], "little"))
	AS7341_4_CH6.append(int.from_bytes(frame_byte_temp[45], "little"))
	AS7341_4_CH7.append(int.from_bytes(frame_byte_temp[46], "little"))
	AS7341_4_CH8.append(int.from_bytes(frame_byte_temp[47], "little"))
	AS7341_4_CH9.append(int.from_bytes(frame_byte_temp[48], "little"))
	AS7341_4_CH10.append(int.from_bytes(frame_byte_temp[49], "little"))

	AS7341_5_CH1.append(int.from_bytes(frame_byte_temp[50], "little"))
	AS7341_5_CH2.append(int.from_bytes(frame_byte_temp[51], "little"))
	AS7341_5_CH3.append(int.from_bytes(frame_byte_temp[52], "little"))
	AS7341_5_CH4.append(int.from_bytes(frame_byte_temp[53], "little"))
	AS7341_5_CH5.append(int.from_bytes(frame_byte_temp[54], "little"))
	AS7341_5_CH6.append(int.from_bytes(frame_byte_temp[55], "little"))
	AS7341_5_CH7.append(int.from_bytes(frame_byte_temp[56], "little"))
	AS7341_5_CH8.append(int.from_bytes(frame_byte_temp[57], "little"))
	AS7341_5_CH9.append(int.from_bytes(frame_byte_temp[58], "little"))
	AS7341_5_CH10.append(int.from_bytes(frame_byte_temp[59], "little"))

	AS7341_6_CH1.append(int.from_bytes(frame_byte_temp[60], "little"))
	AS7341_6_CH2.append(int.from_bytes(frame_byte_temp[61], "little"))
	AS7341_6_CH3.append(int.from_bytes(frame_byte_temp[62], "little"))
	AS7341_6_CH4.append(int.from_bytes(frame_byte_temp[63], "little"))
	AS7341_6_CH5.append(int.from_bytes(frame_byte_temp[64], "little"))
	AS7341_6_CH6.append(int.from_bytes(frame_byte_temp[65], "little"))
	AS7341_6_CH7.append(int.from_bytes(frame_byte_temp[66], "little"))
	AS7341_6_CH8.append(int.from_bytes(frame_byte_temp[67], "little"))
	AS7341_6_CH9.append(int.from_bytes(frame_byte_temp[68], "little"))
	AS7341_6_CH10.append(int.from_bytes(frame_byte_temp[69], "little"))

	SIDE_1_TEMP.append(struct.unpack('f', frame_byte_temp[70]))
	SIDE_2_TEMP.append(struct.unpack('f', frame_byte_temp[71]))
	SIDE_3_TEMP.append(struct.unpack('f', frame_byte_temp[72]))
	SIDE_4_TEMP.append(struct.unpack('f', frame_byte_temp[73]))
	SIDE_5_TEMP.append(struct.unpack('f', frame_byte_temp[74]))
	SIDE_6_TEMP.append(struct.unpack('f', frame_byte_temp[75]))

	SIDE_1_HUMD.append(struct.unpack('f', frame_byte_temp[76]))
	SIDE_2_HUMD.append(struct.unpack('f', frame_byte_temp[77]))
	SIDE_3_HUMD.append(struct.unpack('f', frame_byte_temp[78]))
	SIDE_4_HUMD.append(struct.unpack('f', frame_byte_temp[79]))
	SIDE_5_HUMD.append(struct.unpack('f', frame_byte_temp[80]))
	SIDE_6_HUMD.append(struct.unpack('f', frame_byte_temp[81]))

    # Needs to be calculated to basic counts
    # counts = raw / (gain_val * (getATIME() + 1) * (getASTEP() + 1) * 2.78 / 1000);
	# for ii in np.arange(SIDE_CNT * AS7341_CH_CNT):
	# 	print(int.from_bytes(frame_byte_temp[10 + ii], "little"))
	# 	AS7341[ii].append(int.from_bytes(frame_byte_temp[10 + ii], "little"))

with open("HEXSENSE_12.csv", "r") as f:
	for i, line in enumerate(f):
		line_list = line.strip().split(',')
		process_file(line_list)

# plt.plot(AS7341_1_CH1, label = 'AS7341_1_CH1')
# plt.plot(AS7341_1_CH2, label = 'AS7341_1_CH2')
# plt.plot(AS7341_1_CH3, label = 'AS7341_1_CH3')
# plt.plot(AS7341_1_CH4, label = 'AS7341_1_CH4')
# plt.plot(AS7341_1_CH5, label = 'AS7341_1_CH5')
# plt.plot(AS7341_1_CH6, label = 'AS7341_1_CH6')
# plt.plot(AS7341_1_CH7, label = 'AS7341_1_CH7')
# plt.plot(AS7341_1_CH8, label = 'AS7341_1_CH8')
plt.plot(AS7341_1_CH9, label = 'AS7341_1_CH9')
# plt.plot(AS7341_1_CH10, label = 'AS7341_1_NIR')

# plt.plot(AS7341_2_CH1, label = 'AS7341_1_CH1')
# plt.plot(AS7341_2_CH2, label = 'AS7341_1_CH2')
# plt.plot(AS7341_2_CH3, label = 'AS7341_1_CH3')
# plt.plot(AS7341_2_CH4, label = 'AS7341_1_CH4')
# plt.plot(AS7341_2_CH5, label = 'AS7341_1_CH5')
# plt.plot(AS7341_2_CH6, label = 'AS7341_1_CH6')
# plt.plot(AS7341_2_CH7, label = 'AS7341_1_CH7')
# plt.plot(AS7341_2_CH8, label = 'AS7341_1_CH8')
plt.plot(AS7341_2_CH9, label = 'AS7341_2_CH9')
# plt.plot(AS7341_2_CH10, label = 'AS7341_1_NIR')

# plt.plot(AS7341_3_CH1, label = 'AS7341_1_CH1')
# plt.plot(AS7341_3_CH2, label = 'AS7341_1_CH2')
# plt.plot(AS7341_3_CH3, label = 'AS7341_1_CH3')
# plt.plot(AS7341_3_CH4, label = 'AS7341_1_CH4')
# plt.plot(AS7341_3_CH5, label = 'AS7341_1_CH5')
# plt.plot(AS7341_3_CH6, label = 'AS7341_1_CH6')
# plt.plot(AS7341_3_CH7, label = 'AS7341_1_CH7')
# plt.plot(AS7341_3_CH8, label = 'AS7341_1_CH8')
plt.plot(AS7341_3_CH9, label = 'AS7341_3_CH9')
# plt.plot(AS7341_3_CH10, label = 'AS7341_1_NIR')

# plt.plot(AS7341_4_CH1, label = 'AS7341_1_CH1')
# plt.plot(AS7341_4_CH2, label = 'AS7341_1_CH2')
# plt.plot(AS7341_4_CH3, label = 'AS7341_1_CH3')
# plt.plot(AS7341_4_CH4, label = 'AS7341_1_CH4')
# plt.plot(AS7341_4_CH5, label = 'AS7341_1_CH5')
# plt.plot(AS7341_4_CH6, label = 'AS7341_1_CH6')
# plt.plot(AS7341_4_CH7, label = 'AS7341_1_CH7')
# plt.plot(AS7341_4_CH8, label = 'AS7341_1_CH8')
plt.plot(AS7341_4_CH9, label = 'AS7341_4_CH9')
# plt.plot(AS7341_4_CH10, label = 'AS7341_1_NIR')

# plt.plot(AS7341_5_CH1, label = 'AS7341_1_CH1')
# plt.plot(AS7341_5_CH2, label = 'AS7341_1_CH2')
# plt.plot(AS7341_5_CH3, label = 'AS7341_1_CH3')
# plt.plot(AS7341_5_CH4, label = 'AS7341_1_CH4')
# plt.plot(AS7341_5_CH5, label = 'AS7341_1_CH5')
# plt.plot(AS7341_5_CH6, label = 'AS7341_1_CH6')
# plt.plot(AS7341_5_CH7, label = 'AS7341_1_CH7')
# plt.plot(AS7341_5_CH8, label = 'AS7341_1_CH8')
plt.plot(AS7341_5_CH9, label = 'AS7341_5_CH9')
# plt.plot(AS7341_5_CH10, label = 'AS7341_1_NIR')

# plt.plot(AS7341_6_CH1, label = 'AS7341_1_CH1')
# plt.plot(AS7341_6_CH2, label = 'AS7341_1_CH2')
# plt.plot(AS7341_6_CH3, label = 'AS7341_1_CH3')
# plt.plot(AS7341_6_CH4, label = 'AS7341_1_CH4')
# plt.plot(AS7341_6_CH5, label = 'AS7341_1_CH5')
# plt.plot(AS7341_6_CH6, label = 'AS7341_1_CH6')
# plt.plot(AS7341_6_CH7, label = 'AS7341_1_CH7')
# plt.plot(AS7341_6_CH8, label = 'AS7341_1_CH8')
plt.plot(AS7341_6_CH9, label = 'AS7341_6_CH9')
# plt.plot(AS7341_6_CH10, label = 'AS7341_1_NIR')

# plt.plot(SIDE_1_TEMP, label = 'SIDE_1_TEMP')
# plt.plot(SIDE_2_TEMP, label = 'SIDE_2_TEMP')
# plt.plot(SIDE_3_TEMP, label = 'SIDE_3_TEMP')
# plt.plot(SIDE_4_TEMP, label = 'SIDE_4_TEMP')
# plt.plot(SIDE_5_TEMP, label = 'SIDE_5_TEMP')
# plt.plot(SIDE_6_TEMP, label = 'SIDE_6_TEMP')

# plt.plot(SIDE_1_HUMD, label = 'SIDE_1_HUMD')
# plt.plot(SIDE_2_HUMD, label = 'SIDE_2_HUMD')
# plt.plot(SIDE_3_HUMD, label = 'SIDE_3_HUMD')
# plt.plot(SIDE_4_HUMD, label = 'SIDE_4_HUMD')
# plt.plot(SIDE_5_HUMD, label = 'SIDE_5_HUMD')
# plt.plot(SIDE_6_HUMD, label = 'SIDE_6_HUMD')

# plt.plot(Internal_Temp, label = 'Internal_Temp')
# plt.plot(Bat_v, label = 'Bat_v')
plt.legend()

plt.show()

# print(time_stamp)
# print(Seq_num)




