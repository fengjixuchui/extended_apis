//
// Bareflank Extended APIs
// Copyright (C) 2018 Assured Information Security, Inc.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <bfvmm/vcpu/vcpu_factory.h>
#include <eapis/vcpu/arch/intel_x64/vcpu.h>

using namespace eapis::intel_x64;

// -----------------------------------------------------------------------------
// Handlers
// -----------------------------------------------------------------------------

bool
test_handler(
    gsl::not_null<vmcs_t *> vmcs, msrs::info_t &info)
{ bfignored(vmcs); bfignored(info); return true; }

// -----------------------------------------------------------------------------
// vCPU
// -----------------------------------------------------------------------------

namespace test
{

class vcpu : public eapis::intel_x64::vcpu
{
public:

    /// Default Constructor
    ///
    /// @expects
    /// @ensures
    ///
    vcpu(vcpuid::type id) :
        eapis::intel_x64::vcpu{id}
    {
        this->enable_msr_trapping();

        if (!ndebug) {
            msrs()->enable_log();
        }

        msrs()->trap_on_all_rdmsr_accesses();
        msrs()->trap_on_all_wrmsr_accesses();

        msrs()->pass_through_rdmsr_access(0x000000000000003B); // IA32_TSC_ADJUST
        msrs()->pass_through_wrmsr_access(0x000000000000080B); // IA32_X2APIC_EOI

        msrs()->add_rdmsr_handler(
            0x000000000000003B,
            msrs::handler_delegate_t::create<test_handler>()
        );

        msrs()->add_wrmsr_handler(
            0x000000000000080B,
            msrs::handler_delegate_t::create<test_handler>()
        );
    }

    /// Destructor
    ///
    /// @expects
    /// @ensures
    ///
    ~vcpu() = default;
};

}

// -----------------------------------------------------------------------------
// vCPU Factory
// -----------------------------------------------------------------------------

namespace bfvmm
{

std::unique_ptr<vcpu>
vcpu_factory::make_vcpu(vcpuid::type vcpuid, bfobject *obj)
{
    bfignored(obj);
    return std::make_unique<test::vcpu>(vcpuid);
}

}
