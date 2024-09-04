// Модель для сущности Editor базы данных

#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class Editor : public QObject
{
    Q_OBJECT
public:
    explicit Editor(QObject *parent = nullptr);
    QString getTextEditor() const;
    QString getFileFormats() const;
    QString getEncoding() const;
    bool getHasIntelligence() const;
    bool getHasPlugins() const;
    bool getCanCompile() const;
    void setTextEditor(QString textEditor);
    void setFileFormats(QString fileFormats);
    void setEncoding(QString encoding);
    void setHasIntelligence(bool hasIntelligence);
    void setHasPlugins(bool hasPlugins);
    void setCanCompile(bool canCompile);

private:
    QString textEditor;
    QString fileFormats;
    QString encoding;
    bool hasIntelligence;
    bool hasPlugins;
    bool canCompile;

signals:
};

#endif // EDITOR_H
