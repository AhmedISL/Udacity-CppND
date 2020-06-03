#include "graphedge.h"
#include "graphnode.h"

// constructor
GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode() {}  // destructor

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
{
    std::unique_ptr<GraphEdge> smart_edge(edge);  // create a smart pointer using raw edge pointer
    _childEdges.emplace_back(std::move(smart_edge));
}

void GraphNode::MoveChatbotHere(ChatBot chatBot)
{
    _chatBot = std::move(chatBot); 
    _chatBot.GetChatLogicHandle()->SetChatbotHandle(&_chatBot);  // set the ChatLogic _chatBot handle
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(std::move(_chatBot));
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    return _childEdges[index].get();
}