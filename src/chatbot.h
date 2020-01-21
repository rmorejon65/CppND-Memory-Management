#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <iostream>
#include <string>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation

    //// STUDENT CODE
    ////
    void SetImage(std::string filename);
    ChatBot(const ChatBot &source);
    ChatBot &operator=(const ChatBot &source) {
        if (this == &source)
            return *this;
         std::cout << "ChatBot Copy Assignment Operator" << std::endl;
        _chatLogic = source._chatLogic;
        _rootNode = source._rootNode;
         if (_image != NULL)
        {
            delete _image;
            _image = NULL;
        }
        if (source._image != NULL)
        {
            _image = new wxBitmap(); 
            *_image = *(source._image);
        }
        //std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
        return *this;
    };
    ChatBot(ChatBot &&source);
    ChatBot &operator=(ChatBot &&source) { 
        std::cout << "ChatBot Move Assignment Operator" << std::endl;
        if (this == &source)
            return *this;
        _chatLogic = source._chatLogic;
        _rootNode = source._rootNode;
        _image = source._image; 
        source._chatLogic = nullptr;
        source._rootNode = nullptr;
        source._image = NULL;
        //std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
        return *this;
    };
    ~ChatBot();
    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */