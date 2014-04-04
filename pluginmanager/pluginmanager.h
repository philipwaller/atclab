#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H


#include <QMap>
#include <QString>

class ITaskFactory;


class PluginManager
{

public:
    explicit PluginManager();
    ~PluginManager();

    void loadAllPlugins();
    void loadPlugin(const QString &filename);

    ITaskFactory* lookup(const QString &key) const;

private:
    QMap<QString, ITaskFactory*> plugins_;


};


#endif // PLUGINMANAGER_H
