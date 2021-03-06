/*
  LibISDB
  Copyright(c) 2017-2018 DBCTRADO

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 @file   H265ParserFilter.hpp
 @brief  H.265 解析フィルタ
 @author DBCTRADO
*/


#ifndef LIBISDB_H265_PARSER_FILTER_H
#define LIBISDB_H265_PARSER_FILTER_H


#include "VideoParser.hpp"
#include "../../../../MediaParsers/H265Parser.hpp"


namespace LibISDB::DirectShow
{

	/** H.265 解析フィルタクラス */
	class __declspec(uuid("0F3CFFD1-C30D-43f7-B4DC-57E5F73D074A")) H265ParserFilter
		: public ::CTransInPlaceFilter
		, public VideoParser
		, protected H265Parser::AccessUnitHandler
	{
	public:
		static IBaseFilter * WINAPI CreateInstance(LPUNKNOWN pUnk, HRESULT *phr);

		DECLARE_IUNKNOWN

	// CTransInPlaceFilter
		HRESULT CheckInputType(const CMediaType *mtIn) override;
		HRESULT StartStreaming() override;
		HRESULT StopStreaming() override;
		HRESULT BeginFlush() override;

	protected:
		H265ParserFilter(LPUNKNOWN pUnk, HRESULT *phr);
		~H265ParserFilter();

	// CTransInPlaceFilter
		HRESULT Transform(IMediaSample *pSample) override;
		HRESULT Receive(IMediaSample *pSample) override;

	// H265Parser::AccessUnitHandler
		virtual void OnAccessUnit(const H265Parser *pParser, const H265AccessUnit *pAccessUnit) override;

		H265Parser m_H265Parser;
	};

}	// namespace LibISDB::DirectShow


#endif	// ifndef LIBISDB_H265_PARSER_FILTER_H
