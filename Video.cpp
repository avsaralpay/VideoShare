#include "Video.hpp"

ostream& operator<<(ostream& out, const Video & video) {
    out << "title:" << video.title << ",genre:" << video.genre << endl;
    return out;
}

/* TO-DO: method implementations below */
 
Video::Video()    //video default constructor
{
    title = "";
    genre = "";
}
Video::Video(string p_title, string p_genre) //video constructor
{
    title = p_title;
    genre = p_genre;
}
Video::~Video()
{
    ;           //destructor no need
}
const string& Video::getTitle() const
{
    return title;           
}

void Video::setTitle(const string& p_title)
{   
    title = p_title;
}

const string& Video::getGenre() const
{
    return genre;
}

void Video::setGenre(const string& p_genre)
{
    genre = p_genre;
}

bool Video::operator==(const Video & rhs) const
{
    if(this->getTitle() == rhs.getTitle())
        return true;                //if videos title are equal then videos are the same
    else
        return false;
}