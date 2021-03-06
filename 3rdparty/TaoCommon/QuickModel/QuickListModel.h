#pragma once

#include "QuickListModelBase.h"
#include "TaoCommonGlobal.h"
class TAO_API QuickListModel : public QuickListModelBase
{
    Q_OBJECT
    Q_PROPERTY(bool allChecked READ allChecked WRITE setAllChecked NOTIFY allCheckedChanged)
    Q_PROPERTY(int visibledCount READ visibledCount NOTIFY visibledCountChanged)
    Q_PROPERTY(int selectedCount READ selectedCount NOTIFY selectedCountChanged)
    Q_PROPERTY(int checkedCount READ checkedCount NOTIFY checkedCountChanged)

    Q_PROPERTY(QStringList headerRoles READ headerRoles WRITE setHeaderRoles NOTIFY headerRolesChanged)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    Q_PROPERTY(QString sortRole READ sortRole WRITE setSortRole NOTIFY sortRoleChanged)

public:
    explicit QuickListModel(QObject *parent = nullptr);
    ~QuickListModel() override;

    //[begin] check
    bool allChecked() const
    {
        return mAllChecked;
    }
    Q_INVOKABLE void check(int row, bool checked);
    //[end] check

    //[begin] search. control visible
    Q_INVOKABLE void search(const QString &searchKey);
    //控制显示隐藏的回调。返回true则show，返回false则hide
    using VisibleCallback = std::function<bool(QuickItemBase *)>;
    void setVisibleFilter(const VisibleCallback &callback)
    {
        mVisibleCallback = callback;
    }
    //[end] search

    //[begin] select
    Q_INVOKABLE void deselectAll();
    Q_INVOKABLE void selectAll();
    Q_INVOKABLE bool isSelected(int row) const;
    Q_INVOKABLE void select(int row);
    Q_INVOKABLE void deselect(int row);
    Q_INVOKABLE void selectRange(int from, int to);
    Q_INVOKABLE void selectSingle(int row);
    //[end] select

    Q_INVOKABLE void doPress(int row, bool shift, bool ctrl, bool outRange);
    Q_INVOKABLE void doMove(int row, bool outRange);
    Q_INVOKABLE void doRelease();

    //[begin] sort
    const QStringList &headerRoles() const
    {
        return mHeaderRoles;
    }

    Qt::SortOrder sortOrder() const
    {
        return mSortOrder;
    }

    const QString &sortRole() const
    {
        return mSortRole;
    }
    using SortCallback = std::function<bool(QuickItemBase *, QuickItemBase *)>;
    //Map <key, callBack> ,key should match to headerRoles
    void setSortCallbacks(const QMap<QString, SortCallback> &callbacksMap)
    {
        mSortCallbacks = callbacksMap;
    }
    Q_INVOKABLE void sortByRole();
    //[end] sort

    //[begin] count
    int visibledCount() const
    {
        return mVisibledCount;
    }

    int selectedCount() const
    {
        return mSelectedCount;
    }

    int checkedCount() const
    {
        return mCheckedCount;
    }
    const QString &searchKey() const
    {
        return mSearchkey;
    }
    //[end] count

    void updateCalcInfo() override;

public slots:
    void setAllChecked(bool allChecked);

    void setHeaderRoles(const QStringList &headerRoles);

    void setSortOrder(Qt::SortOrder sortOrder);

    void setSortRole(const QString &sortRole);

    void setVisibledCount(int visibledCount);
    void setSelectedCount(int selectedCount);
    void setCheckedCount(int checkedCount);

signals:

    void allCheckedChanged(bool allChecked);
    void visibledCountChanged(int visibledCount);

    void selectedCountChanged(int selectedCount);

    void checkedCountChanged(int checkedCount);

    void headerRolesChanged(const QStringList &headerRoles);

    void sortOrderChanged(Qt::SortOrder sortOrder);

    void sortRoleChanged(const QString &sortRole);

    void signalUpdateCalcCount();
private:
    void updateAllCheck();
    void updateVisibleCount();
    void updateSelectedCount();
    void updateCheckedCount();
    void updateAlternate();

private:
    bool                        mAllChecked = false;
    int                         mVisibledCount = 0;
    int                         mSelectedCount = 0;
    int                         mCheckedCount = 0;
    QStringList                 mHeaderRoles;
    Qt::SortOrder               mSortOrder = Qt::AscendingOrder;
    QString                     mSortRole;
    QMap<QString, SortCallback> mSortCallbacks;
    QString                     mSearchkey;
    VisibleCallback             mVisibleCallback;
    bool                        mIsPressed = false;
    int                         mLastPressedRow = -1;
};
