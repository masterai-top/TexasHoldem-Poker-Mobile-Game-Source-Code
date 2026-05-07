#pragma once
#include <string>
#include "servant/Application.h"
#include "Java2RoomProto.h"
#include "RoomServant.h"

using namespace JFGame;

class AuditClubRequest
{
    friend class AuditClubRespons;
public:
    AuditClubRequest() {}
    AuditClubRequest(const std::string &json)
    {
        this->Deserialize(json);
    }
    template <typename Writer>
    void Serialize(Writer &writer) const
    {
        writer.StartObject();
        SERIALIZE_MEMBER(writer, iType);
        SERIALIZE_MEMBER(writer, sIds);
        SERIALIZE_MEMBER(writer, sUid);
        writer.EndObject();
    }

    void toString(std::string &json)
    {
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        Serialize(writer);
        json = sb.GetString();
    }

    void Deserialize(const string &json)
    {
        try
        {
            Document d;
            if (d.Parse(json.c_str()).HasParseError())
            {
                throw logic_error("parse json error. raw data : " + json);
            }
            SET_DOC_MEMBER(d, iType);
            SET_DOC_MEMBER(d, sIds);
            SET_DOC_MEMBER(d, sUid);
        }
        catch (const std::exception &e)
        {
            std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":AuditClubRequest decode error!");
            throw logic_error(errInfo);
        }
    }

    std::vector<long> getIds()
    {
        std::vector<long> vResult;
        if (_sIds.isNull())
        {
            return vResult;
        }
        std::string strInfo = _sIds;
        std::vector<std::string> vecStr = split(strInfo, ",");
        for (auto &item : vecStr)
        {
            long id = S2L(item);
            vResult.push_back(id);

        }
        return vResult;
    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        return 0;
    }

private:
    CInteger _iType;        // 操作类型 0: 拒绝， 1: 同意
    CString  _sIds;         // 审请信息唯一ID
    CString _sUid;          // 会长UID     
};
class AuditClubRespons
{
public:
    AuditClubRespons() {}
    AuditClubRespons(const string &json)
    {
        this->Deserialize(json);
    }
    template <typename Writer>
    void Serialize(Writer &writer) const
    {
        writer.StartObject();
        SERIALIZE_MEMBER(writer, iType);
        SERIALIZE_MEMBER(writer, sSuccIds);
        SERIALIZE_MEMBER(writer, sFailIds);
        writer.EndObject();
    }

    void toString(std::string &json)
    {
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        Serialize(writer);
        json = sb.GetString();
    }

    void Deserialize(const string &json)
    {
        Document d;
        if (d.Parse(json.c_str()).HasParseError())
        {
            throw logic_error("parse json error. raw data : " + json);
        }
        SET_DOC_MEMBER(d, iType);
        SET_DOC_MEMBER(d, sSuccIds);
        SET_DOC_MEMBER(d, sFailIds);
    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        FUNC_ENTRY("");
        __TRY__

        // STEP1 解码
        AuditClubRequest request;
        decode(reqBuf, request);

        // STEP2 具体业务处理
        int64_t resultCode = RESULT_CODE_SUCCESS;
        string sSuccIds;
        string sFailIds;
        std::vector<long> vResultIds;
        std::vector<long> vReqIds = request.getIds();
       
        Club::InnerClubAuditListReq req;
        Club::InnerClubAuditListResp resp;
        req.uId = S2L(request._sUid);
        req.ids = vReqIds;
        req.agree = request._iType == 0 ? false : true;
        int iRet = g_app.getOuterFactoryPtr()->getSocialServerPrx(req.uId)->InnerClubAuditList(req, resp);
        if (iRet != 0)
        {
            ROLLLOG_ERROR << "InnerClubAuditList failed, iRet:" << iRet << endl;
            resultCode = RESULT_CODE_FAIL;
        }
        vResultIds.insert(vResultIds.begin(), resp.ids.begin(), resp.ids.end());
        
        for(auto uid : vReqIds)
        {
            auto it = std::find_if(vResultIds.begin(), vResultIds.end(), [uid](long r_uid)->bool{
                return uid == r_uid;
            });
            if(it != vResultIds.end())
            {
                sSuccIds += L2S(uid) + ",";
            }
            else
            {
                sFailIds += L2S(uid) + ",";
            }
        }

        sSuccIds = sSuccIds.length() > 0 ? sSuccIds.substr(0, sSuccIds.length() - 1) : sSuccIds;
        sFailIds = sFailIds.length() > 0 ? sFailIds.substr(0, sFailIds.length() - 1) : sFailIds;

        // STEP3 填充数据
        encode(resultCode, request, rspBuf, sSuccIds, sFailIds);
        
        __CATCH__
        FUNC_EXIT("", 0);
        return 0;
    }

private:

    static void encode(int64_t resultCode, AuditClubRequest &request, vector<tars::Char> &rspBuf, const string &sSuccIds, const string &sFailIds)
    {
        AuditClubRespons  response;
        response._iType.assign(request._iType);
        response._sSuccIds.assign(sSuccIds);
        response._sFailIds.assign(sFailIds);

        // resultData是数组
        std::string json;
        response.toString(json);
        std::string resultData = "[" + json + "]";

        int64_t totalItems = 1;  //总条数
        int64_t totalPages = 1;  //总页数
        GMResponse rsp(resultCode, "", resultData, totalItems, totalPages);
        std::string resultJson;
        rsp.toString(resultJson);
        rspBuf.assign(resultJson.begin(), resultJson.end());
    }

private:
    CInteger _iType;       // 操作类型 0: 拒绝加入俱乐部， 1: 同意加入俱乐部
    CString  _sSuccIds;    // 成功的id
    CString  _sFailIds;    // 失败的id
};