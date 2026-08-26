#ifndef MEDIA_H
#define MEDIA_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Media;
}
QT_END_NAMESPACE

class Media : public QMainWindow
{
    Q_OBJECT

  public:
    Media(QWidget *parent = nullptr);
    ~Media();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::Media *ui;
};
#endif // MEDIA_H
