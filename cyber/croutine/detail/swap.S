/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifdef __aarch64__

.macro push_v_regs_d
    sub sp, sp, #128
    st1 {v8.8H, v9.8H}, [sp], #32
    st1 {v10.8H, v11.8H}, [sp], #32
    st1 {v12.8H, v13.8H}, [sp], #32
    st1 {v14.8H, v15.8H}, [sp]
.endm 

.macro pop_v_regs_d
    ld1 {v14.8H, v15.8H}, [sp]
    sub sp, sp, #32
    ld1 {v12.8H, v13.8H}, [sp]
    sub sp, sp, #32
    ld1 {v10.8H, v11.8H}, [sp]
    sub sp, sp, #32
    ld1 {v8.8H, v9.8H}, [sp]
    add sp, sp, #128 
.endm

#endif

.globl ctx_swap
.type  ctx_swap, @function
ctx_swap:
#if defined(__x86_64__)
      pushq %rdi
      pushq %r12
      pushq %r13
      pushq %r14
      pushq %r15
      pushq %rbx
      pushq %rbp
      movq %rsp, (%rdi)

      movq (%rsi), %rsp
      popq %rbp
      popq %rbx
      popq %r15
      popq %r14
      popq %r13
      popq %r12
      popq %rdi
#elif defined(__aarch64__)
      sub sp, sp, #0xb0
      stp x30, x0, [sp, #0xa0]
      stp x19, x20, [sp, #0x90]
      stp x21, x22, [sp, #0x80]
      stp x23, x24, [sp, #0x70]
      stp x25, x26, [sp, #0x60]
      stp x27, x28, [sp, #0x50]
      stp x29, x30, [sp, #0x40]
//      str x0, [sp, #0x60]
      stp d8, d9, [sp, #0x30]
      stp d10, d11, [sp, #0x20]
      stp d12, d13, [sp, #0x10]
      stp d14, d15, [sp, #0x00]
      mov x4, sp
      str x4, [x0, #0x0]

      ldr x19, [x1, #0x0]
      mov sp, x19
      ldp x19, x20, [sp, #0x90]
      ldp x21, x22, [sp, #0x80]
      ldp x23, x24, [sp, #0x70]
      ldp x25, x26, [sp, #0x60]
      ldp x27, x28, [sp, #0x50]
      ldp x29, x30, [sp, #0x40]
//      ldr x4, [sp, #0x60]
      ldp d8,  d9,  [sp, #0x30]
      ldp d10, d11, [sp, #0x20]
      ldp d12, d13, [sp, #0x10]
      ldp d14, d15, [sp, #0x00]
      ldp x30, x0, [sp, #0xa0]
      add sp, sp, #0xb0
#endif
      ret
