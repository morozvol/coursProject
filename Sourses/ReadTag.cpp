//
// Created by Владимир on 24.10.2018.
//
#include "ReadTag.h"
#include <iostream>
#include "fileref.h"
#include "taglib.h"
using namespace std;
string name =R"(C:/Clion/id3Editor/cmake-build-debug/song1.mp3)";
string name1 =R"(C:/Users/Владимир/Downloads/Shahriyor-Ayt-qachon.mp3)";
int main(){
     TagLib :: FileRef f ( name.c_str() );
     f.tag () -> setAlbum ( "Fillmore East" );
     f.tag () -> setArtist ( "Fill" );
     f.tag () -> setComment ( "ghghgggggggggggggyuf7uyifugugughuhihjo" );
     f.tag () -> setYear (1256);
     f.save ();
    TagLib :: FileRef g ( name1.c_str() );
    cout<< g.tag() ->year()<<endl<<g.tag()->album()<<endl<<g.tag()->artist()<<endl<<g.tag()->comment()<<endl<<endl<<g.tag()->genre()<<endl<<g.tag()->title()<<endl<<g.tag()->track()<<"\n\n\n";
    cout<< f.tag() ->year()<<endl<<f.tag()->album()<<endl<<f.tag()->artist()<<endl<<f.tag()->comment()<<endl<<f.tag()->genre()<<endl<<f.tag()->title()<<endl<<f.tag()->track();

    return 0;
}

