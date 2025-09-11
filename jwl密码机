#define _CRT_SECURE_NO_WARNINGS 1
#include<bits/stdc++.h>
using namespace std;

// 用于替换0-7的八个汉字(GBK编码)
const char* chars[] = { "贾", "筱", "雨", "王", "瀚", "翧", "李", "骁" };

// 加密函数：将字符串加密为指定汉字序列
char* encode(const char* input) {
	if (input == NULL) return NULL;

	int len = strlen(input);
	int num_groups = (len + 2) / 3;  // 计算需要的组数，向上取整
	int output_len = num_groups * 8 * 2 + 1;  // 每个汉字占2字节(GBK)，8个一组
	char* output = (char*)malloc(output_len);
	if (output == NULL) return NULL;

	int out_idx = 0;

	for (int i = 0; i < len; i += 3) {
		// 读取3个字符，不足则用0填充
		unsigned char c1 = (i < len) ? input[i] : 0;
		unsigned char c2 = (i + 1 < len) ? input[i + 1] : 0;
		unsigned char c3 = (i + 2 < len) ? input[i + 2] : 0;

		// 位拆分逻辑
		int group1 = (c1 >> 5) & 0x07;                 // c1的高3位
		int group2 = (c1 >> 2) & 0x07;                 // c1的中3位
		int group3 = ((c1 & 0x03) << 1) | (c2 >> 7);   // c1的低2位 + c2的高1位
		int group4 = (c2 >> 4) & 0x07;                 // c2的中3位
		int group5 = (c2 >> 1) & 0x07;                 // c2的低3位的高3位
		int group6 = ((c2 & 0x01) << 2) | (c3 >> 6);   // c2的最低1位 + c3的高2位
		int group7 = (c3 >> 3) & 0x07;                 // c3的中3位
		int group8 = c3 & 0x07;                        // c3的低3位

		// 存储对应汉字(GBK编码每个汉字2字节)
		strcpy(output + out_idx, chars[group1]);
		out_idx += 2;  // GBK汉字固定2字节
		strcpy(output + out_idx, chars[group2]);
		out_idx += 2;
		strcpy(output + out_idx, chars[group3]);
		out_idx += 2;
		strcpy(output + out_idx, chars[group4]);
		out_idx += 2;
		strcpy(output + out_idx, chars[group5]);
		out_idx += 2;
		strcpy(output + out_idx, chars[group6]);
		out_idx += 2;
		strcpy(output + out_idx, chars[group7]);
		out_idx += 2;
		strcpy(output + out_idx, chars[group8]);
		out_idx += 2;
	}

	output[out_idx] = '\0';
	return output;
}

// 查找汉字对应的数字(GBK编码)
int find_char_index(const char* str) {
	for (int i = 0; i < 8; i++) {
		// 比较两个字节，判断是否为同一个GBK汉字
		if (str[0] == chars[i][0] && str[1] == chars[i][1]) {
			return i;
		}
	}
	return -1;  // 未找到
}

// 解密函数：将汉字序列解密为原始字符串
char* decode(const char* input) {
	if (input == NULL) return NULL;

	int len = strlen(input);
	const int char_len = 2;  // GBK编码每个汉字固定2字节

	// 检查输入长度是否合法
	if (len % char_len != 0) return NULL;
	int num_chars = len / char_len;
	if (num_chars % 8 != 0) return NULL;

	int num_groups = num_chars / 8;
	int output_len = num_groups * 3 + 1;
	char* output = (char*)malloc(output_len);
	if (output == NULL) return NULL;

	int out_idx = 0;
	char current_char[3];  // 存储当前汉字(GBK 2字节+结束符)
	current_char[2] = '\0';

	for (int i = 0; i < num_chars; i += 8) {
		int groups[8];

		// 提取8个汉字对应的数字
		for (int j = 0; j < 8; j++) {
			int pos = (i + j) * char_len;
			current_char[0] = input[pos];
			current_char[1] = input[pos + 1];
			groups[j] = find_char_index(current_char);

			if (groups[j] == -1) {  // 无效字符
				free(output);
				return NULL;
			}
		}

		// 位重组逻辑
		unsigned char c1 = (groups[0] << 5) | (groups[1] << 2) | ((groups[2] >> 1) & 0x03);
		unsigned char c2 = ((groups[2] & 0x01) << 7) | (groups[3] << 4) | (groups[4] << 1) | ((groups[5] >> 2) & 0x01);
		unsigned char c3 = ((groups[5] & 0x03) << 6) | (groups[6] << 3) | groups[7];

		output[out_idx++] = c1;
		output[out_idx++] = c2;
		output[out_idx++] = c3;
	}

	output[out_idx] = '\0';
	return output;
}

int main() {
	// 确保所有汉字在GBK编码下都是2字节
	for (int i = 0; i < 8; i++) {
		if (strlen(chars[i]) != 2) {
			cout << "错误：所有汉字必须是GBK编码的2字节字符" << endl;
			return 1;
		}
	}

	while (1) {
		int op;
		cout << "jwl密码机\n按1回车后输入需要加密内容\n按2回车后输入需要解密内容\n按0退出\n";
		cin >> op;
		cin.ignore();  // 忽略输入缓冲区中的换行符

		if (op == 1) {
			cout << "请输入需要加密内容：";
			char ori[10000];
			cin.getline(ori, sizeof(ori));
			char* encoded = encode(ori);
			if (encoded) {
				printf("加密后: %s\n", encoded);
				free(encoded);
			}
			else {
				printf("加密失败\n");
			}
		}
		else if (op == 2) {
			cout << "请输入需要解密内容：";
			char ori[10000];
			cin.getline(ori, sizeof(ori));
			char* decoded = decode(ori);
			if (decoded) {
				printf("解密后: %s\n", decoded);
				free(decoded);
			}
			else {
				printf("解密失败，输入可能包含无效字符或格式错误\n");
			}
		}
		else if (op == 0) {
			printf("程序退出\n");
			break;
		}
		else {
			printf("无效操作，请输入1(加密)、2(解密)或0(退出)\n");
		}
	}

	return 0;
}
