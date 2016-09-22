#pragma once

enum class OperationKind {
    Move,
    Copy,
};

HRESULT AddOperation(OperationKind kind, IUnknown* items, IShellItem* dest);
