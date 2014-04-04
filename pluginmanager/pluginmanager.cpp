#include "pluginmanager.h"

#include <QDir>
#include <QDebug>
#include <QPluginLoader>

#include "itaskfactory.h"


PluginManager::PluginManager() : plugins_() {};

PluginManager::~PluginManager() {
    foreach (ITaskFactory* plugin , plugins_) {
        delete plugin;
    }
}

void PluginManager::loadAllPlugins() {
    QDir path(QDir::currentPath());
    path.cdUp();
    path.cd("PlugIns");
    qDebug() << "PlugIns Directory: " << path.absolutePath();

    foreach (QString filename, path.entryList(QDir::Files)) {
        loadPlugin(path.absolutePath() + "/" + filename);
    }
}

void PluginManager::loadPlugin(const QString &filename) {
    QPluginLoader loader(filename);
    QObject *possiblePlugin = loader.instance();
    if (!possiblePlugin) return;

    ITaskFactory *plugin = qobject_cast<ITaskFactory*>(possiblePlugin);
    if (!plugin) return;

    qDebug() << QString("... plugin loaded : %1 ...").arg(plugin->type());
    plugins_.insert(plugin->type(), plugin);
}


ITaskFactory* PluginManager::lookup(const QString &key) const{
    if (!plugins_.contains(key)) return 0;
    return plugins_.value(key);
}
