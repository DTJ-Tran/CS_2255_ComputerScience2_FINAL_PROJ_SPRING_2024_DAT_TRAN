#include "CommentMenu.h"

CommentMenu::CommentMenu() : Menu("Comment Space", std::vector<std::string>()) {
    std::vector<std::string> option ;
    option.push_back("Write New Comment");
    option.push_back("Show All Comment");
    option.push_back("Edit Comment");
    option.push_back("Delete Comment");
    setOption(option);
    setCommentHandling();

};

CommentMenu::CommentMenu(std::string specifiedName) : Menu(specifiedName, std::vector<std::string>()) {
    std::vector<std::string> option ;
    option.push_back("Write New Comment");
    option.push_back("Show All Comment");
    option.push_back("Edit Comment");
    option.push_back("Delete Comment");
    setOption(option);
    setCommentHandling();

};

int CommentMenu::getWriteNewCom() {
    return WRITE_NEW_COMMENT;
    };

int CommentMenu::getShowAll() {
    return SHOW_ALL_COMMENT;
    };

int CommentMenu::getEdit() {
    return EDIT_COMMENT;
    };

int CommentMenu::getDelete() {
    return DELETE_COMMENT;
    };


Comment* CommentMenu::getCommentHandling() const {
    return (this->CommendHandling);
    };

void CommentMenu::setCommentHandling() {
    this->CommendHandling = new Comment();
    return;
    };


void CommentMenu::handleChoice(int choice) {

    switch(choice){
        case WRITE_NEW_COMMENT:
            getCommentHandling()->writeNewComment();
            break;
        case SHOW_ALL_COMMENT:
            getCommentHandling()->showAllComments();
            break;
        case DELETE_COMMENT:
            getCommentHandling()->deleteComment();
            break;
        case EDIT_COMMENT:
            getCommentHandling()->editComment(getCommentHandling()->getCommentList());
            break;
        default:
            break;
    }
    return;
};

CommentMenu::~CommentMenu() {
    if (CommendHandling != nullptr) {
            delete CommendHandling;
        }
};