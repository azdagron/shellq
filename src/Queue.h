#pragma once

enum class OperationKind {
    Move,
    Copy,
};

HRESULT AddOperation(OperationKind kind, IUnknown* items, IShellItem* dest);
HRESULT RunOperation(OperationKind kind, IUnknown* items, IShellItem* dest);
