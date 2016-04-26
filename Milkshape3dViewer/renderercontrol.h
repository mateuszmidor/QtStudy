#ifndef RENDERERCONTROL
#define RENDERERCONTROL

#include <QObject>
class RendererControl : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString modelFilename READ getModelFilename WRITE setModelFilename NOTIFY modelFilenameChanged)
    QString modelFilename;

public:
    QString getModelFilename() const {
        return modelFilename;
    }

    void setModelFilename(const QString &value) {
        if (modelFilename != value) {
            modelFilename = value;
            emit modelFilenameChanged();
        }
    }

signals:
    void modelFilenameChanged();
};

#endif // RENDERERCONTROL

