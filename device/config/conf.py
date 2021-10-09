# xtl
import json
import binascii

json_root_dir = 'json_file/'

file_object = open('product_type.txt')
try:
    product_type = file_object.read()  # 获取产品类型配置文件名称
finally:
    file_object.close()

product_type = product_type.strip('\n')
with open(json_root_dir + product_type, 'r', encoding='utf8')as config:
    json_conf = json.load(config)
    print('读到的MX5配置:', json_conf)
    # print(json_conf[0]['confVersion'])

ARRAY_HEAD = 'const unsigned char tlv_config'
ARRAY_BRA = '[ ] = {'
ARRAY_BRA_END = '};'
global ARRAY_XA_HEAD
ARRAY_XA_HEAD = '0xAA,0x55'  # 0x55AA 小端
ARRAY_XA_TAIL = ',0xA5'


def aDDtlv2Array(T, L, V):
    global ARRAY_XA_HEAD
    ARRAY_XA_HEAD += T
    ARRAY_XA_HEAD += L
    ARRAY_XA_HEAD += V


base = [str(x) for x in range(10)] + [chr(x) for x in range(ord('A'), ord('A') + 6)]


def dec2hex(string_num):
    num = int(string_num)
    mid = []
    while True:
        if num == 0: break
    num, rem = divmod(num, 16)
    mid.append(base[rem])

    return ''.join([str(x) for x in mid[::-1]])


def getHexString(str, length):
    hex_heard = ''
    i = 0
    if length % 2 != 0:  # 如果是奇数,说明第一个字符最前面是0x0开头 先把第一个字符提取出来
        eleOdd = str[0:1]
        i = 1;
        hex_heard += ',' + '0x' + eleOdd
    while i < length:
        ele = str[i:i + 2]
        i += 2
        hex_heard += ',' + '0x' + ele
    return hex_heard


def addSettingTlv(typeTag, jsonList, index):  # 注意 此处未对超过255的value值进行处理,传入会出错

    if typeTag == 1:
        print('超速语音报警开关')
        value = jsonList[index]['value']  # 获取json中的value值  不能超过255（暂时未处理！！！）
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))  # 获取10进制对应16进制字符串后,计算元素个数
        aDDtlv2Array(",0x01", ',' + ovLength, ',' + hex(value))  # 对应TAG:0x01 下同
    elif typeTag == 2:
        print('移动语音报警开关')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x02", ',' + ovLength, ',' + hex(value))
    elif typeTag == 3:
        print('默认语音系数')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x03", ',' + ovLength, ',' + hex(value))
    elif typeTag == 4:
        print('夜间语音使能')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x04", ',' + ovLength, ',' + hex(value))
    elif typeTag == 5:
        print('电池仓锁类型')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x05", ',' + ovLength, ',' + hex(value))
    elif typeTag == 6:
        print('后轮锁类型')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x06", ',' + ovLength, ',' + hex(value))
    elif typeTag == 7:
        print('震动报警上报使能')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x07", ',' + ovLength, ',' + hex(value))
    elif typeTag == 8:
        print('大灯控制类型')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x08", ',' + ovLength, ',' + hex(value))
    elif typeTag == 9:
        print('控制器类型')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x09", ',' + ovLength, ',' + hex(value))
    elif typeTag == 10:
        print('BMS类型')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x0A", ',' + ovLength, ',' + hex(value))
    elif typeTag == 11:
        print('电池额定电压类型')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x0B", ',' + ovLength, ',' + hex(value))
    elif typeTag == 12:
        print('头盔锁类型')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x0C", ',' + ovLength, ',' + hex(value))
    elif typeTag == 13:
        print('自动落锁使能')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x0D", ',' + ovLength, ',' + hex(value))
    elif typeTag == 14:
        print('控制器限速值')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x0E", ',' + ovLength, ',' + hex(value))
    elif typeTag == 15:
        print('自动落锁使能')
        value = jsonList[index]['value']
        ovLength = hex(int((len(hex(value)) - 2) / 2 + 0.5))
        aDDtlv2Array(",0x0F", ',' + ovLength, ',' + hex(value))

if 'confVersion' in json_conf.keys():  # confVersion
    val = json_conf['confVersion']
    str_16 = binascii.hexlify(val.encode('utf-8')).decode('utf-8')  # 获取ascii码的字符串
    # print(str_16)
    str_hex = getHexString(str_16, len(str_16))
    # print(str_hex)
    length = hex(int((len(str_16) / 2) + 0.5))  # 获取数组元素的大小的字符串 两个字符串代表一个元素 如果是奇数就+1
    # print(length)
    aDDtlv2Array(",0xF0", ',' + length, str_hex)


if 'productName' in json_conf.keys():  # productName
    val = json_conf['productName']
    str_16 = binascii.hexlify(val.encode('utf-8')).decode('utf-8')
    # print(str_16)
    str_hex = getHexString(str_16, len(str_16))
    # print(str_hex)
    length = hex(int((len(str_16) / 2) + 0.5))
    # print(length)
    aDDtlv2Array(",0xF1", ',' + length, str_hex)

if 'productType' in json_conf.keys():  # productType
    val = json_conf['productType']
    Length = hex(int((len(hex(val)) - 2) / 2 + 0.5))
    aDDtlv2Array(",0xF2", ',' + Length, ',' + hex(val))


if 'setting' in json_conf.keys():  # 解析setting 里的值
    i = 0
    setNum = len(json_conf['setting'])
    while i < setNum:
        type_tagNum = json_conf['setting'][i]['type']
        addSettingTlv(type_tagNum, json_conf['setting'], i)
        i = i + 1
    print(json_conf['setting'])

if __name__ == "__main__":
    str_array = ARRAY_HEAD + ARRAY_BRA + ARRAY_XA_HEAD + ARRAY_XA_TAIL + ARRAY_BRA_END
    print(str_array)
    fw = open('default_config.txt', "w", encoding='utf-8')
    fw.write(str_array)
    fw.close()
