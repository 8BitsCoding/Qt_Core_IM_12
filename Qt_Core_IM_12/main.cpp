#include <QtCore/QCoreApplication>

#include <qdebug.h>
#include <qsettings.h>
#include <qstringlist.h>
#include <qrandom.h>

void saveAge(QSettings* setting, QString group, QString name, int age) {
	setting->beginGroup(group);
	setting->setValue(name, age);
	setting->endGroup();
}

int getAge(QSettings* setting, QString group, QString name) {
	setting->beginGroup(group);

	if (!setting->contains(name)) {
		qWarning() << "Does not contain" << name << " in" << group;
		setting->endGroup();
		return 0;
	}

	bool ok;
	int value = setting->value(name).toInt(&ok);
	setting->endGroup();

	if (!ok) {
		qWarning() << "Failed to convert at int!!!";
		return 0;
	}

	return value;
}

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	QCoreApplication::setOrganizationName("voidrealms");
	QCoreApplication::setOrganizationDomain("VoidRealms.com");
	QCoreApplication::setApplicationName("Tester");

	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	saveAge(&settings, "people", "Bryan", 44);
	saveAge(&settings, "bear", "twoheart", 1);
	saveAge(&settings, "bear", "Bryan", 2);

	QStringList people;
	people << "Bryan" << "Tammy" << "Heather" << "chris";

	foreach(QString person, people) {
		int value = QRandomGenerator::global()->bounded(100);
		saveAge(&settings, "test", person, value);
	}

	// Ensure it saved!
	settings.sync();

	qInfo() << settings.fileName();
	// Window의 경우 레지스트리 정보
	// UNIX 계열의 경우 파일정보가 나타난다.

	foreach(QString group, settings.childGroups()) {
		settings.beginGroup(group);
		qInfo() << "Group : " << group;
		foreach(QString key, settings.childKeys()) {
			qInfo() << "... key: " << key << " = " << settings.value(key).toString();
		}
		settings.endGroup();
	}

	return a.exec();
}