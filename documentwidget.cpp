#include "documentwidget.h"
#include "mainwindow.h"
#include "registereduser.h"
#include "documentsdb.h"

QString g_path;
int	m_timevalue;
int	m_currentCredits;


DocumentWidget::DocumentWidget(QWidget *parent, MainWindow* mw, BaseUser *bu,QTabWidget*tab) : QWidget(parent)
{
    //set up Timer
    m_tab=tab;
    m_parent = mw;
    m_baseUser=bu;
    isFirstTime=true;
    RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);
    m_currentCredits=t->getNumOfCredits();
    createLayouts(); //Create layout within Document Tab
    createActions();
}

//Layout for the Document Tab
void DocumentWidget::createLayouts()
{
    QWidget* widget = new QWidget();
    RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);

    //Create the text edit
    m_txt = new QTextEdit(widget); //Create a Text Box Widget
    m_txt->setPlaceholderText("Open a book, its text goes here!");
    m_txt->setReadOnly(true);
    m_reportText = new QTextEdit(widget); //Create a Report Box Widget
    m_reportText->setPlaceholderText("Write your report here");
    m_reviewText = new QTextEdit(widget); //Create a Review Box Widget
    m_reviewText->setPlaceholderText("Write your review here");

    //Create the Line Edit
    m_searchLine = new QLineEdit(widget);
    m_searchLine->setPlaceholderText("Type what you want to search here");

    //Create Labels
    m_rating = new QLabel("Rate this book:");
    m_searchLabel=new QLabel("Search:");
    m_rating = new QLabel("Rate this book:");
    m_time = new QLabel("Time:0:00");
    m_credits = new QLabel("Credits:"+QString::number(t->getNumOfCredits()));

    //Create the buttons
    m_reviewButton = new QPushButton("Review Document");
    m_reviewButton->setMaximumSize(QSize(150,50));
    m_reportButton = new QPushButton("Report Document");
    m_reportButton->setMaximumSize(QSize(150, 50));
    m_closeButton = new QPushButton("Close Document");
    m_closeButton->setMaximumSize(QSize(150, 50));
    m_submitReview = new QPushButton("Submit Review");
    m_submitReview->setMaximumSize(QSize(150, 50));
    m_hideReview = new QPushButton("Hide Review Box");
    m_hideReview->setMaximumSize(QSize(150, 50));
    m_hideReport = new QPushButton("Hide Report Box");
    m_hideReport->setMaximumSize(QSize(150, 50));
    m_submitReport = new QPushButton("Submit Report");
    m_submitReport->setMaximumSize(QSize(150, 50));
    m_clearReport = new QPushButton("Clear Report");
    m_clearReport->setMaximumSize(QSize(150, 50));
    m_clearReview = new QPushButton("Clear Review");
    m_clearReview->setMaximumSize(QSize(150, 50));
    m_searchButton = new QPushButton("Search");
    m_searchButton->setMaximumSize(QSize(150, 50));

    //Create the Slider with initial values
    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setRange(0, 5);
    m_slider->setValue(4);

    //Create the Spin box
    m_box = new QSpinBox;
    m_box->setRange(0, 5);
    m_box->setValue(4);

    //Create the timer
    m_timer = new QTimer(this);
    m_timevalue = 0;

    //Create the Layout
    m_buttonLayout = new QHBoxLayout();
    m_creditLayout = new QHBoxLayout();
    m_reviewLayout = new QVBoxLayout();
    m_reviewButtonLayout = new QHBoxLayout();
    m_ratingLayout = new QHBoxLayout();
    m_reportLayout = new QHBoxLayout();
    m_searchLayout = new QHBoxLayout();
    m_mainLayout = new QVBoxLayout(widget);

    //Set the widgets into layout
    m_creditLayout->addWidget(m_time);
    m_creditLayout->addWidget(m_credits);
    m_mainLayout->addLayout(m_creditLayout);//Place the credit layout into main layout
    m_searchLayout->addWidget(m_searchLabel);
    m_searchLayout->addWidget(m_searchLine);
    m_searchLayout->addWidget(m_searchButton);
    m_mainLayout->addLayout(m_searchLayout);
    m_mainLayout->addWidget(m_txt); //Place the Text Box Widget into the main layout
    m_buttonLayout->addWidget(m_reviewButton);
    m_buttonLayout->addWidget(m_reportButton);
    m_buttonLayout->addWidget(m_closeButton);
    m_mainLayout->addLayout(m_buttonLayout);//Place the buttons layout into the main layout
    m_ratingLayout->addWidget(m_slider);
    m_ratingLayout->addWidget(m_box);
    m_reviewButtonLayout->addWidget(m_clearReview);
    m_reviewButtonLayout->addWidget(m_hideReview);
    m_reviewButtonLayout->addWidget(m_submitReview);
    m_reviewLayout->addWidget(m_reviewText);
    m_mainLayout->addLayout(m_reviewLayout);//Place the review layout into main layout
    m_mainLayout->addWidget(m_rating);
    m_mainLayout->addLayout(m_ratingLayout);//Place the rating layout into main layout
    m_mainLayout->addLayout(m_reviewButtonLayout);//Place the review button layout into main layout
    m_mainLayout->addWidget(m_reportText);
    m_reportLayout->addWidget(m_clearReport);
    m_reportLayout->addWidget(m_hideReport);
    m_reportLayout->addWidget(m_submitReport);
    m_mainLayout->addLayout(m_reportLayout);//Place the Report Layout into main layout

    //Hide the Report and Review Sections initially
    m_clearReview->hide();
    m_hideReport->hide();
    m_reportText->hide();
    m_reviewText->hide();
    m_submitReport->hide();
    m_rating->hide();
    m_box->hide();
    m_slider->hide();
    m_submitReview->hide();
    m_hideReview->hide();
    m_clearReport->hide();
    setLayout(m_mainLayout);
}

//Actions for the buttons
void DocumentWidget::createActions()
{
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(closeFile()));
    connect(m_reviewButton, SIGNAL(clicked()), this, SLOT(showReview()));
    connect(m_hideReview, SIGNAL(clicked()), this, SLOT(hideReview()));
    connect(m_submitReview, SIGNAL(clicked()), this, SLOT(submitReview()));
    connect(m_slider, SIGNAL(valueChanged(int)), m_box, SLOT(setValue(int)));
    connect(m_box, SIGNAL(valueChanged(int)), m_slider, SLOT(setValue(int)));
    connect(m_reportButton, SIGNAL(clicked()), this, SLOT(showReport()));
    connect(m_clearReport, SIGNAL(clicked()), this, SLOT(clearReport()));
    connect(m_hideReport, SIGNAL(clicked()), this, SLOT(hideReport()));
    connect(m_submitReport, SIGNAL(clicked()), this, SLOT(submitReport()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(s_counter()));
    connect(m_timer, SIGNAL(timeout()), m_parent, SLOT(s_updateCredit()));
    connect(m_clearReview, SIGNAL(clicked()), this, SLOT(clearReview()));
    connect(m_searchButton, SIGNAL(clicked()), this, SLOT(s_search()));
}

//Resume the timer
void DocumentWidget::ResumeTimer()
{
    m_timer->blockSignals(false);
}

// Counter Function
void DocumentWidget::s_counter()
{
    if(m_tab->currentIndex()!=2)
        m_timer->blockSignals(true);
    RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);
    QString T;
    m_timevalue++;
    //Check that current credits is not equal to zero if it is close the document
    if (t->getNumOfCredits() == 0)
    {
        closeFile();
        QMessageBox::information(this, tr("Sorry!"),
                                 "You ran out of credits!");
    }

    //Update credits every minute
    int minute=m_timevalue/60;
    if (m_timevalue%60 == 0 && m_baseUser->getUserType() != BaseUser::SUPER)
        t->changeCreditsBy(-1);

    //calculate current credit in every minute
    m_currentCredits=t->getNumOfCredits()-minute;
    m_credits->setText("Credits: "+QString::number(m_currentCredits));
    int leftSecond=m_timevalue%60;

    if(leftSecond<10)
    {
        T=QString::number(minute)+":0"+QString::number(leftSecond);
        m_time->setText("Time:"+T);
    }
    else
    {
        T=QString::number(minute)+":"+QString::number(leftSecond);
        m_time->setText("Time:"+T);
    }
}

//search function
void DocumentWidget::s_search()
{
    QString searchString=m_searchLine->text();
    QTextDocument *document=m_txt->document();

    bool found = false;

    if (isFirstTime == false)
        document->undo();
    if (searchString.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Search Field"),
                                 "Please enter a word.");
        isFirstTime=true;
    }
    else
    {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);
        cursor.beginEditBlock();
        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::red);
        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
            highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);
            if (!highlightCursor.isNull()) {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight,
                                             QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }
        cursor.endEditBlock();
        isFirstTime = false;
        if (found == false) {
            QMessageBox::information(this, tr("Word Not Found"),
                                     "Sorry, the word cannot be found.");
            isFirstTime = true;
        }
    }

    m_searchLine->clear();
}

void DocumentWidget::makeFirstTimeTrue(){
    isFirstTime = true;
}


#include <QLineEdit>

//read the file
void DocumentWidget::readFile(QString path)
{
    RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);
    t->changeCreditsBy(m_currentCredits-t->getNumOfCredits());
    if(t->getUserType() != BaseUser::SUPER) t->changeCreditsBy(-15);
    m_txt->clear();
    g_path = path;
    QFile file(path); //open file
    QString line;
    m_timevalue=0;
    //handle error
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file); //read into file
    while(!in.atEnd())
    {
        line = in.readLine();
        m_txt->append(line);
    }
    file.close(); //close the file
    m_txt->moveCursor(QTextCursor::Start);//move the cursor to the top of the document
    m_timer->start(1000);
}

//close the (current) file
void DocumentWidget::closeFile()
{
    m_txt->clear();
    RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);
    t->changeCreditsBy(m_currentCredits-t->getNumOfCredits());
    m_timer->stop();
    m_tab->setCurrentIndex(0);
}

//Show the Review Box
void DocumentWidget::showReview()
{
    m_clearReview->show();
    m_reviewText->show();
    m_rating->show();
    m_box->show();
    m_slider->show();
    m_hideReview->show();
    m_submitReview->show();
}

//Hide the Review Box
void DocumentWidget::hideReview()
{
    m_clearReview->hide();
    m_reviewText->hide();
    m_rating->hide();
    m_box->hide();
    m_slider->hide();
    m_hideReview->hide();
    m_submitReview->hide();
}

//Getting the review
void DocumentWidget::submitReview()
{
    //U_ID to get rating
    DocumentsDB *d =new DocumentsDB();
    QFileInfo fileInfo(g_path);
    QString filename(fileInfo.fileName());
    QString id = filename.section(".",0,0);
    QString text = m_reviewText->toPlainText();
    bool check = d->userHasRatedBook(m_baseUser->getUsername(), id.toInt());
    if(check == false)
    {
        d->addRatingToDocWithUID(m_baseUser->getUsername(), id.toInt(), m_slider->value(), text);
        m_reviewText->clear();
        QMessageBox::information(this, tr("Sent!"),
                                 "Your Review has been sent!");
    }
    else
    {
        QMessageBox::information(this, tr("Error!"),
                                 "You already reviewed this book!");
    }
}

//Clear the review
void DocumentWidget::clearReview()
{
    m_reviewText->clear();
}

//Get slider value
void DocumentWidget::getSliderValueandQuit()
{
    if (m_slider->value() == m_slider->maximum())
        close();
}

//Show the Report Box
void DocumentWidget::showReport()
{
    m_reportText->show();
    m_clearReport->show();
    m_hideReport->show();
    m_submitReport->show();
}

//Hide the Report Box
void DocumentWidget::hideReport()
{
    m_reportText->hide();
    m_clearReport->hide();
    m_hideReport->hide();
    m_submitReport->hide();
}

//Submit the Report
void DocumentWidget::submitReport()
{
    QString report;
    report = m_reportText->toPlainText();
    DocumentsDB *d =new DocumentsDB();
    QFileInfo fileInfo(g_path);
    QString filename(fileInfo.fileName());
    QString id = filename.section(".",0,0);
    //Check if the user had already reported this book
    bool reported = d->userHasReportedBook(m_baseUser->getUsername(),id.toInt());
    if(reported == false)
    {
        d->addComplaintToDocumentWithUID(m_baseUser->getUsername(),id.toInt(),report);
        m_reportText->clear();
        QMessageBox::information(this, tr("Sent!"),
                                 "Your report has been sent!");
    }
    else
    {
        QMessageBox::information(this, tr("Error!"),
                                 "You already reported this book!");
    }
}

//Clear the report text
void DocumentWidget::clearReport()
{
    m_reportText->clear();
}

//Update credits
void DocumentWidget::updateCredits()
{
    RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);
    m_credits->setText("Credits:"+QString::number(t->getNumOfCredits()));
}
