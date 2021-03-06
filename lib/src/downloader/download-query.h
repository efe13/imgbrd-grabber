#ifndef DOWNLOAD_QUERY_H
#define DOWNLOAD_QUERY_H

#include <QJsonObject>
#include <QString>


class Site;

class DownloadQuery
{
	public:
		// Constructors
		DownloadQuery() = default;
		explicit DownloadQuery(Site *site);
		explicit DownloadQuery(Site *site, const QString &filename, const QString &path);

		// Serialization
		virtual QString toString(const QString &separator) const = 0;
		virtual void write(QJsonObject &json) const = 0;
		virtual bool read(const QJsonObject &json, const QMap<QString, Site*> &sites) = 0;

		// Public members
		Site *site;
		QString filename;
		QString path;
};

#endif // DOWNLOAD_QUERY_H
