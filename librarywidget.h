#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QModelIndex>

class QTableWidget;
class QVBoxLayout;
class QPushButton;
class DocumentsDB;

class LibraryWidget : public QWidget
{
    Q_OBJECT
public:
    LibraryWidget(QWidget *parent = 0);
    ~LibraryWidget();

    void refreshTable();

private:
    QVBoxLayout*        m_mainLayout;
    QHBoxLayout*        m_tablewithpreviewLayout;
    QHBoxLayout*        m_titleLayout;
    QHBoxLayout*        m_authorLayout;
    QHBoxLayout*        m_genreLayout;
    QVBoxLayout*        m_previewLayout;
    QHBoxLayout*        m_previewbuttonLayout;
    QHBoxLayout*        m_ratingLayout;

    QPushButton*        m_refresh;
    QPushButton*        m_hidePreview;
    QPushButton*        m_openBook;

    QTableWidget*       m_tableWidget;
    QTableWidget*       m_previewWidget;

    QTextEdit*          m_previewText;

    QLabel*             m_title;
    QLabel*             m_author;
    QLabel*             m_genre;
    QLabel*             m_rating;
    QLabel*             m_booktitle;
    QLabel*             m_bookauthor;
    QLabel*             m_bookgenre;
    QLabel*             m_bookrating;

    DocumentsDB*        m_db;

    QString             Title;
    QString             Author;
    QString             Genre;
    QString             Rating;

    void populateTable();

    void createWidgets();
    void createLayouts();
    void createActions();

    void removeFileWithID(int id);

public slots:
    void s_refresh();
    void showPreview();
    void hidePreview();
    void selectCell();
};

#endif // LIBRARYWIDGET_H
