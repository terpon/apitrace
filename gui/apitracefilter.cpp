#include "apitracefilter.h"

#include "apitracecall.h"

#include <QDebug>

ApiTraceFilter::ApiTraceFilter(QObject *parent )
    : QSortFilterProxyModel()
{
}

bool ApiTraceFilter::filterAcceptsRow(int sourceRow,
                                      const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariant varientData = sourceModel()->data(index0);
    ApiTraceCall *call = varientData.value<ApiTraceCall*>();

    if (!call)
        return false;

    QString function = call->name;

    //XXX make it configurable
    if (function.contains(QLatin1String("glXGetProcAddress")))
        return false;
    if (function.contains(QLatin1String("wglGetProcAddress")))
        return false;

    QString fullText = call->richText();
    if (function.contains(QLatin1String("glGetString")) &&
        fullText.contains(QLatin1String("GL_EXTENSIONS")))
        return false;

    return true;
}


#include "apitracefilter.moc"
