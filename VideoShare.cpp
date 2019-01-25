#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VideoShare.hpp"
#include "User.hpp"

using namespace std;

void VideoShare::printAllVideos() {
    videos.print();
}

void VideoShare::printAllUsers() {
    users.print();
}

/* TO-DO: method implementations below */
VideoShare::VideoShare()
{
  videos = LinkedList<Video>();
  users = LinkedList<User>();
}
VideoShare::~VideoShare()
{
    videos.clear();
    users.clear();
}

void VideoShare::createUser(const string & userName, const string & name , const string & surname )
{
    User person(userName,name,surname);
    users.insertNode(users.getHead(),person);
}

void VideoShare::loadUsers(const string  & fileName)
{
    ifstream file;
    file.open(fileName.c_str());
    
    string  username,name,surname;
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss,username,';');
        getline(ss,name,';');
        getline(ss,surname,';');
        User person(username,name,surname);
        users.insertNode(users.getHead(),person);
    }
    file.close();
}
void VideoShare::createVideo(const string & title, const string & genre)
{
    Video vid(title,genre);
    videos.insertNode(videos.getHead(),vid);
}
void VideoShare::loadVideos(const string & fileName)
{
    ifstream file;
    file.open(fileName.c_str());

    string  title,genre;
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss,title,';');
        getline(ss,genre,';');
        Video vid(title,genre);
        videos.insertNode(videos.getHead(),vid);
    }
    file.close();
}

void VideoShare::addFriendship(const string & userName1, const string & userName2)
{
    Node<User>* user1 = users.findNode(userName1);
    Node<User>* user2 = users.findNode(userName2);

    if(user1 && user2)
    {
        user1->getDataPtr()->addFriend(user2->getDataPtr());
        user2->getDataPtr()->addFriend(user1->getDataPtr());
    }

}
void VideoShare::removeFriendship(const string & userName1, const string & userName2)
{
        Node<User>* user1 = users.findNode(userName1);
        Node<User>* user2 = users.findNode(userName2);
        if(user1 && user2)
        {
            Node<User*> *tmp1= user1->getDataPtr()->getFriends()->findPrev(user2->getDataPtr());
            Node<User*> *tmp2= user2->getDataPtr()->getFriends()->findPrev(user1->getDataPtr());

            user1->getDataPtr()->getFriends()->deleteNode(tmp1);
            user2->getDataPtr()->getFriends()->deleteNode(tmp2);

        }
}

void VideoShare::updateUserStatus(const string & userName, Status newStatus)
{
    Node<User>* user1 = users.findNode(userName);
    user1->getDataPtr()->updateStatus(newStatus);
}

void VideoShare::subscribe(const string & userName, const string & videoTitle)
{
    Node<User>* user1 = users.findNode(userName);
    Node<Video>* vid = videos.findNode(videoTitle);

    if(user1 && user1->getDataPtr()->getStatus() == ACTIVE)
    {
        if(!(user1->getDataPtr()->getSubscriptions()->findNode(vid->getDataPtr())))
        {
            user1->getDataPtr()->subscribe(vid->getDataPtr());
        }
    }
}
void VideoShare::unSubscribe(const string & userName, const string & videoTitle)
{
    Node<User>* user1 = users.findNode(userName);
    Node<Video>* vid = videos.findNode(videoTitle);

    if(user1 && vid && user1->getDataPtr()->getStatus() == ACTIVE)
    {
        Node<Video*> *tmp1 = user1->getDataPtr()->getSubscriptions()->findPrev(vid->getDataPtr());
        user1->getDataPtr()->getSubscriptions()->deleteNode(tmp1);
    }
}
void VideoShare::deleteUser(const string & userName)
{
   Node<User>* user1 = users.findNode(userName);
	Node<User>* user1prev = users.findPrev(userName);

	Node<User>* userlist = users.first();
	while (userlist && userlist != user1)
	{
		userlist->getDataPtr()->removeFriend(user1->getDataPtr());
		userlist = userlist->getNext();
	}
	users.deleteNode(user1prev);
}
void VideoShare::sortUserSubscriptions(const string & userName)
{
    Node<User>* user1 = users.findNode(userName);
    LinkedList<Video*> *subs = user1->getDataPtr()->getSubscriptions();    
    Node<Video*> *tmp2  = subs->first();
    int length = 0;

    while(tmp2)
    {
        ++length;
        tmp2 = tmp2->getNext();
    }

    bool sorted = false;

    for(int i = 0;(i<length-1)&&!sorted;i++){

        Node<Video*> *tmp1  = subs->first();
        sorted = true;

        for(int j = 1;j<=length-i-1 && tmp1;j++){

            if(tmp1->getData()->getTitle() > tmp1->getNext()->getData()->getTitle())
            {
                subs->swap(j,j-1);
                sorted = false;
            }
            else{
                tmp1 = tmp1->getNext();
            }
        }
    }
}

void VideoShare::printUserSubscriptions(const string & userName)
{
    Node<User>* tmp = users.findNode(userName);
    if(tmp){
        tmp->getDataPtr()->printSubscriptions();
    }
}


void VideoShare::printFriendsOfUser(const string & userName)
{
    Node<User>* tmp = users.findNode(userName);
    if(tmp){
        tmp->getDataPtr()->printFriends();
    }
}

void VideoShare::printCommonSubscriptions(const string & userName1, const string & userName2)
{
    Node<User>* user1 = users.findNode(userName1);
    Node<User>* user2 = users.findNode(userName2);

    LinkedList<Video*> *subs1 = user1->getDataPtr()->getSubscriptions();
    LinkedList<Video*> *subs2 = user2->getDataPtr()->getSubscriptions();

    Node<Video*> *tmp1  = subs1->first();

    while(tmp1)
    {
        Node<Video*> *tmp2  = subs2->first();

        while(tmp2)
        {
           if(tmp1->getData()== tmp2->getData())
           {
               cout<<"title:"<<tmp1->getData()->getTitle()<<",genre:"<<tmp1->getData()->getGenre()<<endl;
           }
           tmp2 = tmp2->getNext();
        }

        tmp1 = tmp1->getNext();
    }
    cout<<endl;
}

void VideoShare::printFriendSubscriptions(const string & userName)
{
    Node<User>* user1 = users.findNode(userName);

    Node<User*>* friends = user1->getDataPtr()->getFriends()->first();
    string mingenre = "";
    string tmpmin = "";
    int passcount = 0;
    int i = 1;

    while(friends)
    {   
        Node<Video*>* subs = friends->getData()->getSubscriptions()->first();
        while(subs)
        {
            ++passcount;
            subs = subs->getNext();
        }
        friends = friends->getNext();
    }
    
    friends = user1->getDataPtr()->getFriends()->first();
    Node<Video*>* subs = friends->getData()->getSubscriptions()->first();

    while(i != passcount)
    {
        Node<User*>* tmp1 = user1->getDataPtr()->getFriends()->first();
        string min = "zzzzzzzzzzzzzzzzzz";

        while(tmp1)
        {
            Node<Video*>* tmp2 = tmp1->getData()->getSubscriptions()->first();
            bool includes = false;

            while(tmp2)
            {
                if(tmp2->getData()->getTitle() <= tmpmin)
                {
                    tmp2 = tmp2->getNext();
                }
                else if(tmp2->getData()->getTitle() < min)
                {
                    min = tmp2->getData()->getTitle();
                    mingenre = tmp2->getData()->getGenre();

                    if(user1->getDataPtr()->getSubscriptions()->findNode(tmp2->getData()))
                    {
                        includes = true;
                    }
                    tmp2 = tmp2->getNext();
                }
                else{
                    tmp2 = tmp2->getNext();
                }
            }
            tmp1 = tmp1 ->getNext();

            if(tmp1 == NULL)
            {
                ++i;

                if(!includes)
                {
                tmpmin = min;
                    if(min != "zzzzzzzzzzzzzzzzzz" )
                    cout<<"title:"<<min<<",genre:"<<mingenre<<endl;
                }
            }
        }
    }
    cout <<endl;
}
bool VideoShare::isConnected(const string & userName1, const string & userName2)
{
    Node<User>* user1 = users.findNode(userName1);
    Node<User>* user2 = users.findNode(userName2);
    
    Node<User*>* friends1 = user1->getDataPtr()->getFriends()->first();
    Node<User*>* friends2 = user2->getDataPtr()->getFriends()->first();
    
    while(friends1){
        if(friends1->getData()->getFriends()->findNode(user2->getDataPtr()))
        {
            return true;
        }
        friends1 = friends1->getNext();
    }
    
    while(friends2){
		if (friends2->getData()->getFriends()->findNode(user1->getDataPtr()))
        {
            return true;
        }
        friends2 = friends2->getNext();
    }
    
    return false;
}



