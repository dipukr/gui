#include <QPair>
#include <QQueue>
#include <QMultiMap>
#include <QDir>
#include <QFile>
#include <QList>
#include <QFileInfo>
#include <QIODevice>
#include <QTextStream>

QTextStream out(stdout);
QTextStream in(stdin);

QMultiMap<QString, QString> files;
int fileCount = 0;
int dirCount = 0;

void parsei(const QDir &dir)
{
	QQueue<QDir> queue;
	queue.enqueue(dir);
	while (!queue.isEmpty()) {
		QDir dir = queue.dequeue();
		foreach (const QFileInfo &info, dir.entryInfoList()) {
			if (info.isFile()) {
				files.insert(info.fileName(), info.absoluteFilePath());
			} else {
				files.insert(info.fileName(), info.absoluteFilePath());
				QDir adir(info.absolutePath()+"/"+info.fileName());
				adir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
				queue.enqueue(adir);			
			}
		}
	}
}


void parse(QDir &dir)
{
	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
	foreach (const QFileInfo &info, dir.entryInfoList()) {
		if (info.isFile()) {
			fileCount++;
			files.insert(info.fileName(), info.absoluteFilePath());
		} else if (info.isDir()) {
			dirCount++;
			files.insert(info.fileName(), info.absoluteFilePath());
			QDir tmp(info.absolutePath()+"/"+info.fileName());
			parse(tmp);
		}
	}
}

void main()
{
	QFile file("files");
	if (!file.open(QIODevice::WriteOnly)) return;
	QTextStream stream(&file);
	QDir dir("D:/");
	parse(dir);
	//QString word="ASP.NET_4.0.30319";
	//QMap<QString, QString>::iterator iter = files.find(word);
	//out << "path of " << word << ": " << iter.value();
	out << "Files: " << fileCount << endl;
	out << "Folders: " << dirCount << endl;
	out << "Objects: " << files.count() << endl;
	QList<QString> values = files.values();
	foreach (const QString &elem, values)
		stream << elem << endl;
	file.close();
}




