#include <stdio.h>
#include <stdlib.h>

#include "ini.h"

size_t _get_file_size(FILE* fp) {
	fseek(fp, 0L, SEEK_END);
	size_t sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	return sz;
}

void _PrintOwner(ini_t* ini) {
	if (ini == NULL) return;
	const char* name = ini_get(ini, "owner", "name");
	const char* organization = ini_get(ini, "owner", "organization");

	printf("\n[ Owner ]\n");
	printf(
		"Owner Name: %s\nOwner Organization: %s\n",
		name == NULL ? "(NULL)" : name,
		organization == NULL ? "(NULL)" : organization
	);
}

void _PrintDatabase(ini_t* ini) {
	if (ini == NULL) return;
	const char* server = ini_get(ini, "database", "server");
	const char* port = ini_get(ini, "database", "port");
	const char* file = ini_get(ini, "database", "file");

	printf("\n[ Database ]\n");
	printf(
		"DB Server: %s\nDB Port: %s\nDB File: %s\n",
		server == NULL ? "(NULL)" : server,
		port == NULL ? "(NULL)" : port,
		file == NULL ? "(NULL)" : file
	);
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s <ini-filepath>\n", argv[0]);
		return 1;
	}

	FILE* fp = fopen(argv[1], "r");
	size_t fSize = _get_file_size(fp);
	printf("Loading File: %s (%ld bytes)\n", argv[1], fSize);

	const char* iniStr = calloc((fSize * sizeof(char) + 1), sizeof(char));
	fread((void*)iniStr, (fSize * sizeof(char)) + 1, 1, fp);
	fclose(fp);
	fp = NULL;

	ini_t* ini_from_file = ini_load(argv[1]);
	ini_t* ini_from_str = ini_load_str(iniStr);

	_PrintOwner(ini_from_file);
	_PrintDatabase(ini_from_str);

	if (iniStr != NULL) {
		free((void*)iniStr);
		iniStr = NULL;
	}
	return 0;
}
