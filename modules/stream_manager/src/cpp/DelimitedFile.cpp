//=============================================================================
// Copyright (c) 2016-2017 Allan CORNET (Nelson)
//=============================================================================
// LICENCE_BLOCK_BEGIN
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// LICENCE_BLOCK_END
//=============================================================================
#include "DelimitedFile.hpp"
#include "Exception.hpp"
#include "characters_encoding.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    NLSSTREAM_MANAGER_IMPEXP void delimitedWrite(ArrayOf mat,
            std::wstring filenameDestination,
            bool bAppend,
            std::wstring delimiter,
            int64 rowsOffset, int64 colsOffset,
            std::wstring formatPrecision,
            bool isNewLinePc)
    {
        bool bTypeSupported = mat.isNumeric() || mat.isLogical();
        if (!bTypeSupported)
        {
            throw Exception(_W("An numeric matrix expected."));
        }
        if (mat.isSparse())
        {
            throw Exception(ERROR_TYPE_NOT_SUPPORTED);
        }
        if (mat.isComplex())
        {
            mat.promoteType(NLS_DCOMPLEX);
        }
        else
        {
            mat.promoteType(NLS_DOUBLE);
        }
        FILE *fw = nullptr;
        if (bAppend)
        {
#ifdef _MSC_BUILD
            fw = _wfopen(filenameDestination.c_str(), L"at");
#else
            fw = fopen(wstring_to_utf8(filenameDestination).c_str(), "at");
#endif
        }
        else
        {
#ifdef _MSC_BUILD
            fw = _wfopen(filenameDestination.c_str(), L"wt");
#else
            fw = fopen(wstring_to_utf8(filenameDestination).c_str(), "wt");
#endif
        }
        if (!fw)
        {
            throw Exception(_W("Impossible to open file."));
        }
        else
        {
            Dimensions dims = mat.getDimensions();
            std::wstring fmt_with_delimiter = formatPrecision + delimiter;
            int64 ymax;
            if (mat.is2D())
            {
                ymax = dims.getColumns() + colsOffset - 1;
            }
            else
            {
                ymax = dims.getElementCount() / dims.getRows() + colsOffset - 1;
            }
            for (int64 x = 1; x <= rowsOffset; x++)
            {
                for (int64 y = 1; y <= ymax; y++)
                {
                    fwprintf(fw, L"%ls", delimiter.c_str());
                }
                if (isNewLinePc)
                {
                    fwprintf(fw, L"%ls", L"\r\n");
                }
                else
                {
                    fwprintf(fw, L"%ls", L"\n");
                }
            }
            if (mat.is2D())
            {
                ymax = dims.getColumns();
            }
            else
            {
                ymax = dims.getElementCount() / dims.getRows();
            }
            if (mat.isComplex())
            {
                doublecomplex* matCplx = reinterpret_cast<doublecomplex*>((double*)mat.getDataPointer());
                for (int64 x = 0; x < (int64)dims.getRows(); x++)
                {
                    for (int64 x = 0; x < colsOffset; x++)
                    {
                        fwprintf(fw, L"%ls", delimiter.c_str());
                    }
                    std::wstring realPartStr = L"";
                    std::wstring imagPartStr = L"";
                    for (int64 y = 0; y < ymax; y++)
                    {
                        doublecomplex val = matCplx[x + y * dims.getRows()];
                        if (std::isnan(val.real()))
                        {
                            realPartStr = L"NaN";
                        }
                        else
                        {
                            if (std::isinf(val.real()))
                            {
                                if (val.real() > 0)
                                {
                                    realPartStr = L"Inf";
                                }
                                else
                                {
                                    realPartStr = L"-Inf";
                                }
                            }
                            else
                            {
                                wchar_t buffer[1024];
                                swprintf(buffer, 1024, formatPrecision.c_str(), val.real());
                                realPartStr = buffer;
                            }
                        }
                        if (std::isnan(val.imag()))
                        {
                            imagPartStr = L"+NaN";
                        }
                        else
                        {
                            if (std::isinf(val.imag()))
                            {
                                if (val.imag() > 0)
                                {
                                    imagPartStr = L"+Inf";
                                }
                                else
                                {
                                    imagPartStr = L"-Inf";
                                }
                            }
                            else
                            {
                                wchar_t buffer[1024];
                                swprintf(buffer, 1024, formatPrecision.c_str(), val.imag());
                                if (val.imag() >= 0)
                                {
                                    imagPartStr = buffer;
                                    imagPartStr = L"+" + imagPartStr;
                                }
                                else
                                {
                                    imagPartStr = buffer;
                                }
                            }
                        }
                        std::wstring numberAsString = realPartStr + imagPartStr + L"i";
                        fwprintf(fw, L"%ls", numberAsString.c_str());
                        if (y < ymax - 1)
                        {
                            fwprintf(fw, L"%ls", delimiter.c_str());
                        }
                    }
                    if (isNewLinePc)
                    {
                        fwprintf(fw, L"%ls", L"\r\n");
                    }
                    else
                    {
                        fwprintf(fw, L"%ls", L"\n");
                    }
                }
            }
            else
            {
                double *pValue = (double*)mat.getDataPointer();
                for (int64 x = 0; x < (int64)dims.getRows(); x++)
                {
                    for (int64 x = 0; x < colsOffset; x++)
                    {
                        fwprintf(fw, L"%ls", delimiter.c_str());
                    }
                    for (int64 y = 0; y < ymax; y++)
                    {
                        double val = pValue[x + y * dims.getRows()];
                        if (std::isnan(val))
                        {
                            fwprintf(fw, L"%ls", L"NaN");
                            if (y < ymax - 1)
                            {
                                fwprintf(fw, L"%ls", delimiter.c_str());
                            }
                        }
                        else
                        {
                            if (std::isinf(val))
                            {
                                if (val > 0)
                                {
                                    fwprintf(fw, L"%ls", L"Inf");
                                }
                                else
                                {
                                    fwprintf(fw, L"%ls", L"-Inf");
                                }
                                if (y < ymax - 1)
                                {
                                    fwprintf(fw, L"%ls", delimiter.c_str());
                                }
                            }
                            else
                            {
                                std::wstring fmt;
                                if (y < ymax - 1)
                                {
                                    fmt = fmt_with_delimiter;
                                }
                                else
                                {
                                    fmt = formatPrecision;
                                }
                                fwprintf(fw, fmt.c_str(), val);
                            }
                        }
                    }
                    if (isNewLinePc)
                    {
                        fwprintf(fw, L"\r\n");
                    }
                    else
                    {
                        fwprintf(fw, L"\n");
                    }
                }
            }
            fclose(fw);
        }
    }
    //=============================================================================
}
//=============================================================================
