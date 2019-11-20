#include <QtCore/QCoreApplication>

#include <qdebug.h>
#include <qsettings.h>

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
	// QCoreApplication::setApplicationName("Tester2");
	// 만약 Application의 이름을 변경하면 아래의 결과는 다르게 나온다.

	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	// Save the setting
	//settings.setValue("test", 123);

	// Read the setting back
	//qInfo() << settings.value("test").toString();
	//qInfo() << settings.value("test").toInt();

	saveAge(&settings, "people", "Bryan", 44);
	saveAge(&settings, "bear", "twoheart", 1);
	saveAge(&settings, "bear", "Bryan", 2);

	qInfo() << "twoheart" << getAge(&settings, "bear", "twoheart");
	qInfo() << "Bryan" << getAge(&settings, "bear", "Bryan");


	return a.exec();
}