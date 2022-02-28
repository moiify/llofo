本应用对固件进行二次打包，为固件加上了带有平台号、固件版本号和内核号的头部
打包完成之后会在原固件目录生成一个带版本号和crc校验的.pack文件

使用方法
1.在powershell进入该目录下
2.输入./pack.exe 固件的文件名 平台号 内核号

eg.
输入:
./pack.exe app.img L610 5.1.9

eg.
打包成功输出:
Package complete!
File is saved in .\out\appimage_debug\hex\app_15.255.16.pack
打包失败输出：
app.img open error 

注：文件名最大为128字节，平台号和版本号最大为16字节，内核号最大为64字节

附：支持的平台

平台                                          内核                                                                   固件版本
SIM800C                           SIM800CB09                                       8开头、32开头(DA14580)，33开头(DA14585)

EC20                      EC20CEFAGR06A06M4G_OCPU                          14开头(DA14580)，16开头(DA14585)

EC20-256           EC20CEFASGR07A04V01M2G_OCPU                      14开头(DA14580)，16开头(DA14585)

EC25A             EC25AFAR05A05M4G_OCPU_01.001.01.002               14开头(DA14580)，16开头(DA14585)

EC25AU          EC25AUFAR06A01M4G_OCPU_01.001.01.001             14开头(DA14580)，16开头(DA14585)

EC25E             EC25EFAR06A02M4G_OCPU_01.001.01.001                14开头(DA14580)，16开头(DA14585)
 
L610                                         5.1.9                                                                       无区分

L610                                        5.2.14                                                                       无区分

注意：L610的5.2.9内核在设备上用ati指令查询显示的是5.1.9，所以这里用5.1.9