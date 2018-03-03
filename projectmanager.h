#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <QVariant>

class QListView;

class ProcessManager;

class ProjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ProjectManager(QListView *view, ProcessManager *pman, QObject *parent = nullptr);
    virtual ~ProjectManager();

    QString projectName() const { return property("project").toString(); }
    bool isProjectOpen() const { return !projectName().isEmpty(); }

signals:
    void projectOpened(const QString& makePath);
    void projectClosed();
    void targetTriggered(const QString& target);
    void requestFileOpen(const QString& path);

public slots:
    void openProject(const QString& makefile);
    void closeProject();

private:
    class Priv_t;
    Priv_t *priv;
};

#endif // PROJECTMANAGER_H
