#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QVariant>
#include "models/image.h"


class Page;

class Downloader : public QObject
{
	Q_OBJECT

	public:
		Downloader() = default;
		~Downloader() override;
		Downloader(Profile *profile, const QStringList &tags, const QStringList &postFiltering, const QList<Site*> &sources, int page, int max, int perPage, const QString &location, const QString &filename, const QString &user, const QString &password, bool blacklist, const QList<QStringList> &blacklistedTags, bool noDuplicates, int tagsMin, const QString &tagsFormat, Downloader *previous = nullptr);
		void setQuit(bool quit);
		void downloadImages(const QList<QSharedPointer<Image>> &images);
		void loadNext();
		void setData(const QVariant &data);
		void getPageCount();
		void getTags();
		void getPageTags();
		void getImages();
		void getUrls();
		QVariant getData() const;
		QList<Page*> getPages() const;
		QList<Site*> getSites() const;
		int ignoredCount() const;
		int duplicatesCount() const;
		int pagesCount() const;
		int imagesMax() const;
		Page *lastPage() const;

	signals:
		void finished(QNetworkReply*);
		void finishedPageCount(int);
		void finishedTags(const QList<Tag> &);
		void finishedPageTags(const QList<Tag> &);
		void finishedImages(const QList<QSharedPointer<Image>> &);
		void finishedImagesPage(Page *page);
		void finishedImage(QSharedPointer<Image> image);
		void finishedUrls(const QStringList &);
		void finishedUrlsPage(Page *page);
		void quit();

	public slots:
		void returnInt(int ret);
		void returnString(const QString &ret);
		void returnTagList(const QList<Tag> &tags);
		void returnStringList(const QStringList &ret);
		void finishedLoadingPageCount(Page *page);
		void finishedLoadingTags(const QList<Tag> &tags);
		void finishedLoadingPageTags(Page *page);
		void finishedLoadingImages(Page *page);
		void finishedLoadingUrls(Page *page);
		void finishedLoadingImage(QSharedPointer<Image> img, const QMap<QString, Image::SaveResult> &result);
		void cancel();
		void clear();

	private:
		Profile *m_profile;
		Page *m_lastPage;
		QStringList m_tags, m_postFiltering;
		QList<Site*> m_sites;
		int m_page, m_max, m_perPage, m_waiting, m_ignored, m_duplicates, m_tagsMin;
		QString m_location, m_filename, m_user, m_password;
		bool m_blacklist, m_noDuplicates;
		QString m_tagsFormat;
		QList<QStringList> m_blacklistedTags;

		QList<Page*> m_pages, m_pagesC, m_pagesT, m_oPages, m_oPagesC, m_oPagesT;
		QList<QSharedPointer<Image>> m_images;
		QList<QPair<Site*, int> > m_pagesP, m_oPagesP;
		QList<Tag> m_results;
		QVariant m_data;
		bool m_cancelled, m_quit;
		Downloader *m_previous;
};

#endif // DOWNLOADER_H
