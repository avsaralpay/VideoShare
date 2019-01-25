#include <iostream>
#include "User.hpp"
#include "Video.hpp"

void User::printSubscriptions() {
    Node< Video*> * first = subscriptions.first();
    while (first) {
        cout << *(first->getData());
        first = first->getNext();
    }
    cout << std::endl;
}

void User::printFriends() {
    Node< User*> * first = friends.first();
    while (first) {
        cout << *(first->getData());
        first = first->getNext();
    }
    cout << std::endl;
}

ostream& operator<<(ostream& out, const User & user) {
    string st = (user.status == ACTIVE) ? "active" : "suspended";
    out << "username:" << user.username << ",name:" << user.name << ",surname:" << user.surname << ",Status:" << st << endl;
    return out;
}

/* TO-DO: method implementations below */

User::User()
{
  username = "";
  name = "";
  surname = "";
  status = ACTIVE;
  subscriptions =  LinkedList<Video*>();
  friends =  LinkedList<User*>();
}
User::User(string username, string name  , string surname  )
{
    this->username = username;
    this->name = name;
    this->surname = surname;
    status = ACTIVE;
    subscriptions = LinkedList<Video*>();
    friends = LinkedList<User*>();
}
User::~User()
{
    subscriptions.clear();
    friends.clear();
}
const string& User::getUsername() const
{
    return username;
}
const string& User::getName() const
{
    return name;
}
const string& User::getSurname() const
{
    return surname;
}
Status User::getStatus()  const
{
    return status;
}

void  User::updateStatus(Status st)
{
    status = st;
}

void User::subscribe(Video * video)
{
    if(subscriptions.getHead() == NULL)
    {
        subscriptions.insertNode(NULL,video);
    }
    else
    {
        subscriptions.insertNode(subscriptions.getHead(),video);
    }
}
void User::unSubscribe(Video * video)
{
    if(subscriptions.first())
    {
        Node<Video*>* temp = subscriptions.findPrev(video);
        subscriptions.deleteNode(temp);
    }
}

void User::addFriend(User * user)
{
    if(friends.getHead() == NULL)
    {
        friends.insertNode(NULL,user);
    }
    else
    {
        friends.insertNode(friends.getHead(),user);
    }
}

void User::removeFriend(User * user)
{
    if(friends.first())
    {
        Node<User*>* temp = friends.findPrev(user);
        friends.deleteNode(temp);
    }
}
LinkedList<Video* >* User::getSubscriptions()
{
    return &subscriptions;
}
LinkedList< User* >* User::getFriends()
{
    return &friends;
}

bool User::operator==(const User& rhs) const
{
    if(username == rhs.getUsername())
    {
        return true;
    }
    else{
        return false;
    }
}
