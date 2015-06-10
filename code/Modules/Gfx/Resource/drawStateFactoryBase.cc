//------------------------------------------------------------------------------
//  drawStateFactoryBase.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "drawStateFactoryBase.h"
#include "Gfx/Resource/drawState.h"
#include "Gfx/Resource/resourcePools.h"

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
drawStateFactoryBase::drawStateFactoryBase() :
renderer(nullptr),
meshPool(nullptr),
programBundlePool(nullptr) {
    // empty
}

//------------------------------------------------------------------------------
drawStateFactoryBase::~drawStateFactoryBase() {
    o_assert_dbg(nullptr == this->renderer);
    o_assert_dbg(nullptr == this->meshPool);
    o_assert_dbg(nullptr == this->programBundlePool);
}

//------------------------------------------------------------------------------
void
drawStateFactoryBase::Setup(class renderer* rendr, class meshPool* mshPool, class programBundlePool* pbPool) {
    o_assert_dbg(nullptr != rendr);
    o_assert_dbg(nullptr != mshPool);
    o_assert_dbg(nullptr != pbPool);
    o_assert_dbg(nullptr == this->renderer);
    o_assert_dbg(nullptr == this->meshPool);
    o_assert_dbg(nullptr == this->programBundlePool);

    this->renderer = rendr;
    this->meshPool = mshPool;
    this->programBundlePool = pbPool;
}

//------------------------------------------------------------------------------
void
drawStateFactoryBase::Discard() {
    o_assert_dbg(nullptr != this->renderer);
    o_assert_dbg(nullptr != this->meshPool);
    o_assert_dbg(nullptr != this->programBundlePool);
    
    this->renderer = nullptr;
    this->meshPool = nullptr;
    this->programBundlePool = nullptr;
}

//------------------------------------------------------------------------------
ResourceState::Code
drawStateFactoryBase::SetupResource(drawState& ds) {
    ds.msh = this->meshPool->Lookup(ds.Setup.Mesh);
    o_assert_dbg(ds.msh && (ResourceState::Valid == ds.msh->State));
    ds.prog = this->programBundlePool->Lookup(ds.Setup.Program);
    o_assert_dbg(ds.prog && (ResourceState::Valid == ds.prog->State));
    return ResourceState::Valid;
}

//------------------------------------------------------------------------------
void
drawStateFactoryBase::DestroyResource(drawState& ds) {
    ds.Clear();
}

} // namespace _priv
} // namespace Oryol
