#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// specifying path for files.
//string musicPath = "C:\\Users\\abdul\\source\\repos\\Assignment2\\Assignment2\\Music.csv";
//string authorsPath = "C:\\Users\\abdul\\source\\repos\\Assignment2\\Assignment2\\Authors.csv";
//string albumsPath = "C:\\Users\\abdul\\source\\repos\\Assignment2\\Assignment2\\Albums.csv";
//string discographyPath = "C:\\Users\\abdul\\source\\repos\\Assignment2\\Assignment2\\Discography.csv";


// defining prototypes
template <typename I, typename S, typename F>
class MMD;  
template <typename I, typename S, typename F>
class AD;  
template <typename I>
class ADP;
template <typename I, typename S>
class AMD;

MMD<int, string, float>* Musichead;
AMD<int, string>* AMDHead;
AD<int, string, float>* albumsHead;
ADP<int>* DIDHead;

//Music Metadata DataBase (A doubly linked list)
template <typename I, typename S, typename F>
class MMD
{
public:
	//data members
	I mbid;
	AD<I, S, F>* album;

	//connections
	MMD<I, S, F>* next;
	MMD<I, S, F>* previous;
	double length;
	S songName;
	S writer;
	MMD() {
		mbid = -1;
		next = NULL;
		previous = NULL;
		songName = "";
		writer = "";
		length = -1;
	}
};

//Author Metadata DataBase (A circular linked list)
template <typename I, typename S>
class AMD
{
public:
	//data members
	I aid;
	I DOB;
	I startOfCareerDate;
	S name;
	S band;
	S gender;
	S genre;
	AD<I, S, float>* albums;
	ADP<I>* adp;

	//connections
	AMD<I, S>* next;

	AMD() {
		aid = -1;
		DOB = -1;
		startOfCareerDate = -1;
		name = "";
		band = "";
		gender = "";
		genre = "";
		albums = NULL;
		adp = NULL;
	}
};

// Tracks (A singly linked list)
template <typename I>
class Tracks
{
public:
	//data members
	I trackNumber;
	MMD<I, string, float>* trackRef;

	//connections
	Tracks* next;
};

//Album DataBase (A circular linked list)
template <typename I, typename S, typename F>
class AD
{
public:
	//data members
	I abid;
	I aid;
	I noOfTracks;
	I totalDuration;
	S albumName;
	S publisher;
	AMD<I, S>* author;
	Tracks<I>* tracks;
	ADP<I>* adp;

	//connections
	AD<I, S, F>* next;
};

//Albums (A singly linked list)
template <typename I>
class Albums
{
public:
	//data members
	I year;
	AD<int, string, float>* albumRef;

	//connections
	Albums* next;
};

//Author Discography Playlist (A circular linked list)
template <typename I>
class ADP
{
public:
	//data members
	I did;
	AMD<I, string>* author;
	Albums<I>* albums;

	//connections
	ADP* next;
};

//Functions Prototypes
template <typename I, typename S, typename F>
MMD<I, S, F>* Create_MMD(S path) { //should return head of the MMD linkedlist
	S buffer;
	S attributeBuffer;
	I i;
	ifstream file;
	Musichead = new MMD<I, S, F>;
	MMD<I, S, F>* itt = Musichead;
	MMD<I, S, F>* prev;
	file.open(path, ios::in);
	if (!file.is_open()) {
		cout << "ERROR, Music File Not Open." << endl;
		exit(0);
	}
	getline(file, buffer);
	while (!file.eof()) {
		getline(file, buffer);
		if (buffer == "") { // at last line of csv file, there is an empty line.
			break;
		}
		i = 0;
		attributeBuffer = ""; // resetting buffer.
		while (buffer[i] != ',') { // copying mbid as S
			attributeBuffer += buffer[i];
			i++;
		}
		if (stoi(attributeBuffer) != 1) {  // creating next node. Will not create for first iteration as it is already present.
			itt->next = new MMD<I, S, F>;
			prev = itt;  // connecting to next and previous node.
			itt = itt->next;
			itt->previous = prev;
		}
		itt->mbid = stoi(attributeBuffer); // converting to int and storing in MMD
		i++;
		attributeBuffer = "";
		while (buffer[i] != ',') { // saving song name
			if (buffer[i] == '\"') {  // for song having commas in its name.
				attributeBuffer += buffer[i];
				i++;
				while (buffer[i] != '\"') {  // copying all characters of that song's name untill next " is not reached.
					attributeBuffer += buffer[i];
					i++;
				}
			}
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		itt->songName = attributeBuffer; // storing song name.
		attributeBuffer = ""; // resetting buffer
		while (buffer[i] != ',') { // saving writer name
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		itt->writer = attributeBuffer; // storing writer name.
		attributeBuffer = "";
		itt->length = stod(buffer.substr(i)); // storing song length as Ieger
	}
	file.close();
	return Musichead;
}
template <typename I, typename S>
AMD<I, S>* Create_AMD(S path) { //should return head of the AMD linkedlist
	AMD<I, S>* head = new AMD<I, S>;
	AMD<I, S>* itt = head;
	ifstream file;
	S buffer, attributeBuffer;
	I i = 0;
	file.open(path, ios::in);
	if (!file.is_open()) {  // check to see if file is opening.
		cout << "ERROR: Authors File Not Open." << endl;
		exit(0);
	}
	getline(file, buffer);
	while (!file.eof()) {
		i = 0;
		getline(file, buffer);
		if (buffer == "") {  // at last line, there is an empty line.
			break;
		}
		attributeBuffer = "";
		while (buffer[i] != ',') { // copying AID Io attributeBuffer as S
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		if (stoi(attributeBuffer) != 1) { // creating next node. Will not create for first iteration as it is already present.
			itt->next = new AMD<I, S>;
			itt = itt->next;
		}
		itt->aid = stoi(attributeBuffer);
		attributeBuffer = "";
		while (buffer[i] != ',') { // copying Name Io attributeBuffer as S
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		itt->name = attributeBuffer;
		attributeBuffer = "";
		while (buffer[i] != ',') { // copying Band Io attributeBuffer as S
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		itt->band = attributeBuffer;
		attributeBuffer = "";
		while (buffer[i] != ',') { // copying Gender Io attributeBuffer as S
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		itt->gender = attributeBuffer;
		attributeBuffer = "";
		while (buffer[i] != ',') { // copying DOB Io attributeBuffer as S
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		itt->DOB = stoi(attributeBuffer);
		attributeBuffer = "";
		while (buffer[i] != ',') { // copying start of career date Io attributeBuffer as S
			attributeBuffer += buffer[i];
			i++;
		}
		i++;
		itt->startOfCareerDate = stoi(attributeBuffer);
		attributeBuffer = "";
		attributeBuffer = buffer.substr(i);  // for last attribute, there is no comma at the end so reading till end of line.
		i++;
		itt->genre = attributeBuffer;
		attributeBuffer = "";
	}
	file.close();
	itt->next = head; // turning it into circular linked list.
	AMDHead = head;
	return head;
}
template <typename I, typename S, typename F>
AD<I, S, F>* Create_AD(S path) {
	AD<I, S, F>* head = new AD<I, S, F>;
	AD<I, S, F>* itt = head;
	itt->tracks = NULL;
	Tracks<I>* tempTrack = NULL;
	MMD<I, S, F>* CheckTrackInAlbum = Musichead;
	AMD<I, S>* checkAuthor = AMDHead;
	Albums<I>* albumItt;
	bool musicCheck;
	ifstream file;
	file.open(path, ios::in);
	S buffer, attributeBuffer, trackBuffer;
	I i = 0;
	I checkMbid;
	if (!file.is_open()) {  // check to see if file is opening.
		cout << "ERROR: Albums File Not Open." << endl;
		exit(0);
	}
	i = 0;
	getline(file, buffer);  // discarding line containing attribut names.
	getline(file, buffer);  // reading first line of data.
	while (!file.eof()) {
		if (buffer == "") {  // at last line of file, there is an empty line.
			break;
		}
		attributeBuffer = "";  // resetting buffer
		i = 0;
		while (buffer[i] != ',') {  // storing ABID in attributeBuffer as S.
			attributeBuffer += buffer[i]; 
			i++;
		}
		if (stoi(attributeBuffer) != 1) { // creating next node. Will not create for first iteration as it is already present.
			itt->next = new AD<I, S, F>;
			itt = itt->next;
			itt->tracks = NULL;
		}
		itt->abid = stoi(attributeBuffer);
		attributeBuffer = ""; // resetting buffer
		i++;
		while (buffer[i] != ',') {  // storing Album Name in attributeBuffer as S.
			attributeBuffer += buffer[i];
			i++;
		}
		itt->albumName = attributeBuffer;
		attributeBuffer = "";  // resetting buffer
		i++;
		while (buffer[i] != ',') {  // storing AID in attributeBuffer as S.
			attributeBuffer += buffer[i];
			i++;
		}
		itt->aid = stoi(attributeBuffer); 
		checkAuthor = AMDHead;
		while (checkAuthor->next != NULL) {  // iterating the AMD(Author Metadata) linklist untill end is reached.
			if (checkAuthor->aid == itt->aid) {  // if AID of this AD(Album database) element and the one on iterator i currently on is same.
				itt->author = checkAuthor;  // poI its author as the author on which oterator is on.
				if (itt->author->albums == NULL) { // if author's album linked list is empty, poI it to this one.
					itt->author->albums = itt;
				}
				break;
			}
			checkAuthor = checkAuthor->next;
		}
		checkAuthor = AMDHead;
		attributeBuffer = "";  // resetting buffer
		i++;
		while (buffer[i] != ',') {  // storing Publisher in attributeBuffer as S.
			attributeBuffer += buffer[i];
			i++;
		}
		itt->publisher = attributeBuffer;
		attributeBuffer = "";  // resetting buffer
		i++;
		while (buffer[i] != ',') {  // storing Number of Tracks in attributeBuffer as S.
			attributeBuffer += buffer[i];
			i++;
		}
		itt->noOfTracks = stoi(attributeBuffer);
		attributeBuffer = "";  // resetting buffer
		i++;
		while (buffer[i] != ',') {  // storing Total Duration in attributeBuffer as S.
			attributeBuffer += buffer[i];
			i++;
		}
		itt->totalDuration = stoi(attributeBuffer);
		attributeBuffer = "";  // resetting buffer
		i++;

		for (I j = 0; j < itt->noOfTracks; j++) {
			i = 0;
			while (buffer[i] != ',') {  // skipping ABID.
				i++;
			}
			i++;
			while (buffer[i] != ',') {  // skipping Album Name.
				i++;
			}
			i++;
			while (buffer[i] != ',') {  // skipping AID.
				i++;
			}
			i++;
			while (buffer[i] != ',') {  // skipping Publisher.
				i++;
			}
			i++;
			while (buffer[i] != ',') {  // skipping Number of Tracks.
				i++;
			}
			i++;
			while (buffer[i] != ',') {  // skipping Total Duration.
				i++;
			}
			i++;
			attributeBuffer = "";  // resetting buffer
			while (buffer[i] != ',') {  // storing track number as S.
				attributeBuffer += buffer[i];
				i++;
			}
			i++;
			if (itt->tracks == NULL) {  // if tracks is not poIing to any track.
				itt->tracks = new Tracks<I>;  // create and link a new tracks node.
				itt->tracks->trackNumber = stoi(attributeBuffer);  // store first track number in it.
				itt->tracks->next = NULL;  // set next of track equal to NULL.
				tempTrack = itt->tracks;  // connect it to iterator for use in later MBID part.
			}
			else {
				tempTrack = itt->tracks;  // connect tracks to temporary iterator.
				while (tempTrack->next != NULL) { // iterate till end of linked list.
					tempTrack = tempTrack->next;
				}
				tempTrack->next = new Tracks<I>;  // add new tracks node at end of linked list.
				tempTrack = tempTrack->next;  // go to newly created node.
				tempTrack->trackNumber = stoi(attributeBuffer);  // update its track number.
				tempTrack->next = NULL;
			}
			attributeBuffer = buffer.substr(i);  // storing mbid as S.
			checkMbid = stoi(attributeBuffer);  // converting to I for comparison as well as storing later on.
			while (CheckTrackInAlbum->next != NULL) {  // iterating through the entire musicHead.
				if (checkMbid == CheckTrackInAlbum->mbid) {  // if track with same mbid found.
					tempTrack->trackRef = CheckTrackInAlbum;  // poI to mmd node.
					tempTrack->trackRef->album = itt;  // make that node poI back to album.
					break;
				}
				CheckTrackInAlbum = CheckTrackInAlbum->next;
			}
			CheckTrackInAlbum = Musichead;
			getline(file, buffer);
		}
		attributeBuffer = "";  // resetting buffer
		i++;
		CheckTrackInAlbum = Musichead;
	}
	albumsHead = head;
	itt->next = head;
	return head;
}
template <typename I>
ADP<I>* Create_ADP(string path) { //should return head of the ADP linkedlist
	ADP<I>* head = NULL;
	ADP<I>* itt = NULL;
	AMD<I, string>* AuthorItt = AMDHead;
	Albums<I>* albumIterator = NULL;
	AD<I, string, float>* albumHeadItt = NULL;
	string buffer, attributeBuffer;
	int i, AIDBuffer, newADPCheck = 0, ABIDCheck = 0, check;
	ifstream file;
	file.open(path, ios::in);
	if (!file.is_open()) {  // check for if file not open.
		cout << "Discography File Not Open." << endl;
		exit(0);
	}
	getline(file, buffer);  // skipping first line.
	getline(file, buffer);  // reading first line of data.
	while (true) {
		if (buffer == "") {
			break;
		}
		if (head == NULL) {
			head = new ADP<I>;
			itt = head;
		}
		else{
			itt->next = new ADP<I>;
			itt = itt->next;
		}
		itt->albums = NULL;
		i = 0;
		attributeBuffer = ""; // resetting attribute buffer.
		while (buffer[i] != ',') {   // storing DID(Discography ID) as string.
			attributeBuffer += buffer[i];
			i++;
		}
		i++; // moving iterator to next char
		itt->did = stoi(attributeBuffer);  // storing DID.
		attributeBuffer = ""; // resetting attribute buffer.
		while (buffer[i] != ',') {   // storing AID as string.
			attributeBuffer += buffer[i];
			i++;
		}
		i++;  // moving iterator to next char
		AIDBuffer = stoi(attributeBuffer);  // storing AID in buffer to be used later.
		while (AuthorItt != NULL) {
			if (AIDBuffer == AuthorItt->aid) {  // if particular AMD Node found.
				itt->author = AuthorItt;  // create link from ADP to AMD
				AuthorItt->adp = itt;  // create link from AMD to ADP
				break;
			}
			AuthorItt = AuthorItt->next;
		}
		attributeBuffer = ""; // resetting attribute buffer.
		while (true) {  // if new DID found.
			i = 0;
			while (buffer[i] != ',') {   // skipping DID.
				i++;
			}
			i++;
			while (buffer[i] != ',') {   // skipping AID.
				i++;
			}
			i++;
			while (buffer[i] != ',') {   // storing Album ABID as string.
				attributeBuffer += buffer[i];
				i++;
			}
			i++;  // moving iterator to next char
			if (itt->albums == NULL) { // if no node exists in linked list.
				itt->albums = new Albums<I>;  // create new node.
				albumIterator = itt->albums;  // make albumIterator point to new node.
			}
			else { // if node already exists.
				albumIterator->next = new Albums<I>;  // create new node on next node.
				albumIterator = albumIterator->next;  //shift to that node.
			}
			albumHeadItt = albumsHead;  // set albumHeadItt to point linked list head.
			ABIDCheck = stoi(attributeBuffer);  // store ABID of particular album.
			while (albumHeadItt != NULL) {  // iterate through entire linked list of album data (AD).
				if (ABIDCheck == albumHeadItt->abid) { // if ABID is found
					albumIterator->albumRef = albumHeadItt;  // create link from itt->album(ADP) to AD node
					albumIterator->albumRef->adp = itt;  // create link from AD node to itt(ADP)
					break;
				}
				albumHeadItt = albumHeadItt->next;
			}
			attributeBuffer = buffer.substr(i);  // store last attribute(year) in attributeBuffer.
			itt->albums->year = stoi(attributeBuffer);  // update year of album in ADP.
			attributeBuffer = "";
			getline(file, buffer);  // get next line.
			if (buffer == "") {
				break;
			}
			check = buffer[0];  // converts ascii into int.
			check -= 48;
			if (check != itt->did) {  // break loop if new Discography record started.
				break;
			}
		}
	}
	DIDHead = head;
	itt->next = head;  // turning it into circular linked list.
	return head;
}
template <typename I, typename S, typename F>
MMD<I, S, F>* Search_Music(I MBID) { //should return poIer to track having mbid = MBID
	MMD<I, S, F>* itt = Musichead;
	while (itt->mbid != MBID) {  // iterating through linked list till MBID not found.
		itt = itt->next;
	}
	return itt;
}
template <typename I, typename S>
AMD<I, S>* Search_Author(I AID) { //should return poIer to author having aid = AID
	AMD<I, S>* itt = AMDHead;
	while (itt->aid != AID) {  // iterating through linked list till AID not found.
		itt = itt->next;
	}
	return itt;
}
template <typename I, typename S, typename F>
AD<I, S, F>* Search_Album(I ABID) { //should return poIer to album having abid = ABID
	AD<I, S, F>* itt = albumsHead;
	while (itt->abid != ABID) {  // iterating through linked list till ABID not found.
		itt = itt->next;
	}
	return itt;
}
template <typename I>
ADP<I>* Search_Discography(I DID) { //should return poIer to discography having did = DID
	ADP<I>* itt = DIDHead;
	while (itt->did != DID) { // iterating through linked list till DID not found.
		itt = itt->next;
	}
	return itt;
}
template <typename I>
Tracks<I>* Search_Music_By_Album(I ABID) { //should return singly linklist of "Tracks" in given album
	AD<I, string, float>* itt = albumsHead;
	while (itt->abid != ABID) {  // iterating through linked list till ABID not found.
		itt = itt->next;
	}
	return itt->tracks;
}
template <typename I>
Albums<I>* Search_Music_By_Author(I DID) { //should return singly linklist of "Albums" in given discography
	ADP<I>* itt = DIDHead;
	while (itt->did != DID) {  // iterating through linked list till DID not found.
		itt = itt->next;
	}
	return itt->albums;


}