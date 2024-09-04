// Модель для сущности Editor базы данных

#include "editor.h"

Editor::Editor(QObject *parent)
    : QObject{parent}
{}

QString Editor::getTextEditor() const {
    return this->textEditor;
}

QString Editor::getFileFormats() const {
    return this->fileFormats;
}

QString Editor::getEncoding() const {
    return this->encoding;
}

bool Editor::getHasIntelligence() const {
    return this->hasIntelligence;
}

bool Editor::getHasPlugins() const {
    return this->hasPlugins;
}

bool Editor::getCanCompile() const {
    return this->canCompile;
}

void Editor::setTextEditor(QString textEditor) {
   this->textEditor = textEditor;
}

void Editor::setEncoding(QString encoding) {
    this->encoding = encoding;
}

void Editor::setFileFormats(QString fileFormats) {
    this->fileFormats = fileFormats;
}

void Editor::setHasIntelligence(bool hasIntelligence) {
    this->hasIntelligence = hasIntelligence;
}

void Editor::setHasPlugins(bool hasPlugins) {
    this->hasPlugins = hasPlugins;
}

void Editor::setCanCompile(bool canCompile) {
    this->canCompile = canCompile;
}
