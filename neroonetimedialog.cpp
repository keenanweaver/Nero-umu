#include "neroonetimedialog.h"
#include "ui_neroonetimedialog.h"
#include "nerofs.h"

NeroOneTimeDialog::NeroOneTimeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeroOneTimeDialog)
{
    ui->setupUi(this);

    // rand + undefined int, bit shifted to only give the three least significant bytes (0-7)
    // THIS can be set before window setup...
    switch(((LOLRANDOM + rand()) >> 29)) {
    case 0: this->setWindowIcon(QIcon(":/ico/narikiri/stahn")); break;
    case 1: this->setWindowIcon(QIcon(":/ico/narikiri/rutee")); break;
    case 2: this->setWindowIcon(QIcon(":/ico/narikiri/mary")); break;
    case 3: this->setWindowIcon(QIcon(":/ico/narikiri/chelsea")); break;
    case 4: this->setWindowIcon(QIcon(":/ico/narikiri/philia")); break;
    case 5: this->setWindowIcon(QIcon(":/ico/narikiri/lilith")); break;
    case 6: this->setWindowIcon(QIcon(":/ico/narikiri/woodrow")); break;
    case 7: this->setWindowIcon(QIcon(":/ico/narikiri/kongman")); break;
    }

    // required for good hidpi icon quality... because Qt doesn't set this automatically?
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QStringList prefixes = NeroFS::GetPrefixes();

    for(const QString prefix : prefixes) {
        prefixesBtns << new QPushButton(prefix);
        connect(prefixesBtns.last(), &QPushButton::clicked, this, &NeroOneTimeDialog::prefixBtn_clicked);
        ui->prefixes->addWidget(prefixesBtns.last());
    }
}

NeroOneTimeDialog::~NeroOneTimeDialog()
{
    delete ui;
}
