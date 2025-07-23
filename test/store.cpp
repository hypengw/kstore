#include <format>
#include <gtest/gtest.h>

#include "kstore/qt/gadget_model.hpp"

struct Model {
    Q_GADGET

    Q_PROPERTY(int uid MEMBER uid)
public:
    int uid;
    int age { 18 };
};

template<>
struct kstore::ItemTrait<Model> {
    using key_type   = int;
    using store_type = kstore::ShareStore<Model>;
    static auto key(kstore::param_type<Model> m) { return m.uid; }
};

struct ListModel : kstore::QGadgetListModel,
                   kstore::QMetaListModelCRTP<Model, ListModel, kstore::ListStoreType::Share> {
    Q_OBJECT
public:
    ListModel(QObject* p = nullptr): kstore::QGadgetListModel(this, p) {}
};

TEST(Store, Basic) {
    kstore::ShareStore<Model> store;

    ListModel m;
    m.set_store(&m, store);
    m.insert(0, std::array { Model { 1 }, Model { 2 } });

    EXPECT_EQ(m.at(0).uid, 1);
    EXPECT_EQ(m.at(1).uid, 2);
}

TEST(Store, Share) {
    kstore::ShareStore<Model> store;

    ListModel m;
    ListModel n;
    m.set_store(&m, store);
    n.set_store(&m, store);
    m.insert(0, std::array { Model { 1 }, Model { 2 } });

    EXPECT_EQ(m.at(0).age, 18);
    EXPECT_EQ(m.at(1).age, 18);

    n.insert(0, std::array { Model { 1, 10 }, Model { 2, 20 } });

    EXPECT_EQ(m.at(0).age, 10);
    EXPECT_EQ(m.at(1).age, 20);
}

#include "store.moc"