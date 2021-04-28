#include "SoundCloud.h"


int main() {
	MMD<int, string, float>* headMMD = Create_MMD<int, string, float>("C:\\Users\\abdul\\source\\repos\\Assignment2\\Assignment2\\Music.csv");
	MMD<int, string, float>* tempMMD = headMMD;
	/*while (tempMMD != NULL) {
		cout << tempMMD->songName << "    " << tempMMD->writer << "    " << tempMMD->mbid << "    " << tempMMD->album << "    " << tempMMD->length << endl;
		tempMMD = tempMMD->next;
	}*/

	AMD<int, string>* headAMD = Create_AMD<int, string>(authorsPath);
	AMD<int, string>* tempAMD = headAMD;
	/*while (tempAMD != NULL) {
		cout << tempAMD->aid << "  " << tempAMD->band << "  " << tempAMD->DOB << "  " << tempAMD->gender << "  " << tempAMD->genre << "  " << tempAMD->name << "  " << tempAMD->startOfCareerDate << endl;
		tempAMD = tempAMD->next;
	}*/
	AD<int, string, float>* headAD = Create_AD<int, string, float>(albumsPath);
	Create_ADP<int>(discographyPath);
	return 0;
}