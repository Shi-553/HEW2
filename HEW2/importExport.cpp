﻿#include <stdio.h>
#include "map.h"
#include "flyingObjectSponer.h"
#include "npc.h"
#include "player.h"
#include "importExport.h"

void StageToSamune(std::string& stagename);


std::string gFilename;
void SetStagePath(std::string filename) {
	gFilename = filename;
}
bool StageExport() {
	FILE* fp = NULL;

	//	バイナリ書き込みモードでファイルを開く
	fopen_s(&fp, gFilename.c_str(), "wb");

	if (fp == NULL) {
		return false;
	}

	ExportStageInfo(fp);

	MapExport(fp);
	FlyingObjectSponerExport(fp);
	PlayerExport(fp);
	NPCExport(fp);

	fclose(fp);

	return true;
}
bool StageImport() {
	FILE* fp = NULL;

	//	バイナリ読み込みモードでファイルを開く
	fopen_s(&fp, gFilename.c_str(), "rb");

	if (fp == NULL) {
		return false;
	}
	std::string samunename = gFilename;
	StageToSamune(samunename);

	ImportStageInfo(fp, samunename);

	MapImport(fp);
	FlyingObjectSponerImport(fp);
	PlayerImport(fp);
	NPCImport(fp);

	SecureMapLabelList();

	fclose(fp);
	return true;
}

void StageToSamune(std::string& stagename) {
	stagename.replace(stagename.size() - 6, 6, ".png");
}

bool GetStageInfos(std::string foldername, std::vector<StageInfo>& infos) {
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	auto search_name = foldername + "\\*";

	hFind = FindFirstFile(search_name.c_str(), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		return false;
	}

	/* 指定のディレクトリ以下のファイル名をファイルがなくなるまで取得する */
	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			/* ディレクトリの場合は何もしない */
			printf("directory\n");
		}
		else {
			std::string filename = std::string(win32fd.cFileName);
			if (filename.rfind(".stage") != filename.size() - 6) {
				continue;
			}

			FILE* fp = NULL;
			std::string filePath=foldername +"\\" + filename;

			fopen_s(&fp, filePath.c_str(), "rb");

			if (fp != NULL) {

				StageToSamune(filePath);
				infos.push_back(ImportStageInfo(fp, filePath));

				fclose(fp);
			}
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return true;
}