import csv
import struct
import numpy as np
import matplotlib.pyplot as plt

time_stamp    = []
Seq_num       = []
ACCX          = []
ACCY          = []
ACCZ          = []
GYROX         = []
GYROY         = []
GYROZ         = []
Internal_Temp = []
AS7341        = [][]

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
	ACCX.append(struct.unpack('f', frame_byte_temp[2]))
	ACCY.append(struct.unpack('f', frame_byte_temp[3]))
	ACCZ.append(struct.unpack('f', frame_byte_temp[4]))
	GYROX.append(struct.unpack('f', frame_byte_temp[5]))
	GYROY.append(struct.unpack('f', frame_byte_temp[6]))
	GYROZ.append(struct.unpack('f', frame_byte_temp[7]))
	Internal_Temp.append(struct.unpack('f', frame_byte_temp[8]))
	AS7341_1_CH1.append(int.from_bytes(frame_byte_temp[9], "little"))
	AS7341_1_CH2.append(int.from_bytes(frame_byte_temp[10], "little"))

with open("HEXSENSE.csv", "r") as f:
	for i, line in enumerate(f):
		line_list = line.strip().split(',')
		process_file(line_list)

print(AS7341_1_CH2)
plt.plot(AS7341_1_CH2)
plt.show()

# print(time_stamp)
# print(Seq_num)


