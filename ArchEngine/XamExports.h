#pragma once


EXTERN_C {
	HRESULT XamUserGetSigninInfo(DWORD dwUserIndex, DWORD dwFlags, XUSER_SIGNIN_INFO* pSigninInfo);

	
D3DVertexShader*       D3DDevice_CreateVertexShader(__in CONST DWORD *pFunction);
D3DPixelShader*        D3DDevice_CreatePixelShader(__in CONST DWORD *pFunction);
D3DBaseTexture*        D3DDevice_CreateTexture(DWORD Width, DWORD Height, DWORD Depth, DWORD Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, D3DRESOURCETYPE D3DType);
D3DSurface*            D3DDevice_CreateSurface(DWORD Width, DWORD Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, CONST D3DSURFACE_PARAMETERS* pParameters);
D3DVertexBuffer*       D3DDevice_CreateVertexBuffer(UINT Length, DWORD Usage, D3DPOOL UnusedPool);
D3DIndexBuffer*        D3DDevice_CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool);
D3DVertexDeclaration*  D3DDevice_CreateVertexDeclaration(__in CONST D3DVERTEXELEMENT9* pVertexElements);
D3DConstantBuffer*     D3DDevice_CreateConstantBuffer(UINT VectorCount, DWORD Usage);
D3DCommandBuffer*      D3DDevice_CreateCommandBuffer(UINT Size, DWORD Flags);
D3DCommandBuffer*      D3DDevice_CreateGrowableCommandBuffer(DWORD Flags, __in D3DALLOCATECALLBACK pAllocateCallback, __in D3DFREECALLBACK pFreeCallback, __in D3DQUERYCALLBACK pQueryCallback, DWORD CallbackContext, DWORD SegmentSize);
D3DQuery*              D3DDevice_CreateQuery(__in D3DDevice *pDevice, D3DQUERYTYPE Type);
D3DQuery*              D3DDevice_CreateQueryTiled(__in D3DDevice *pDevice, D3DQUERYTYPE Type, DWORD TileCount);
D3DVertexDeclaration*  D3DDevice_GetVertexDeclaration(__in D3DDevice *pDevice);
D3DSurface*            D3DDevice_GetRenderTarget(__in D3DDevice *pDevice, DWORD RenderTargetIndex);
D3DSurface*            D3DDevice_GetDepthStencilSurface(__in D3DDevice *pDevice);
D3DSurface*            D3DDevice_GetBackBuffer(__in D3DDevice *pDevice);
D3DTexture*            D3DDevice_GetFrontBuffer(__in D3DDevice *pDevice);
D3DBaseTexture*        D3DDevice_GetTexture(__in D3DDevice *pDevice, DWORD Sampler);
D3DVertexBuffer*       D3DDevice_GetStreamSource(__in D3DDevice *pDevice, UINT StreamNumber, UINT *pOffsetInBytes, UINT *pStride);
D3DIndexBuffer*        D3DDevice_GetIndices(__in D3DDevice *pDevice);
D3DStateBlock*         D3DDevice_CreateStateBlock(__in D3DDevice* pDevice, D3DSTATEBLOCKTYPE Type);
D3DPerfCounters*       D3DDevice_CreatePerfCounters(__in D3DDevice *pDevice, UINT NumInstances);
D3DPerfCounterBatch*   D3DDevice_CreatePerfCounterBatch(__in D3DDevice* pDevice, UINT NumSlots, UINT NumTiles, DWORD Flags);
D3DOcclusionQueryBatch*  D3DDevice_CreateOcclusionQueryBatch(__in D3DDevice* pDevice, UINT NumSlots, UINT NumTiles);

ULONG    D3DDevice_AddRef(__in D3DDevice *pDevice);
ULONG    D3DDevice_Release(__in D3DDevice *pDevice);
VOID     D3DDevice_GetDirect3D(__in D3DDevice *pDevice, __deref_out Direct3D **ppD3D9);
VOID     D3DDevice_GetDeviceCaps(__in D3DDevice *pDevice, D3DCAPS9 *pCaps);
VOID     D3DDevice_GetDisplayMode(__in D3DDevice *pDevice, UINT UnusedSwapChain, D3DDISPLAYMODE *pMode);
VOID     D3DDevice_GetCreationParameters(__in D3DDevice *pDevice, D3DDEVICE_CREATION_PARAMETERS *pParameters);
HRESULT  D3DDevice_Reset(__in D3DDevice *pDevice, __in D3DPRESENT_PARAMETERS *pPresentationParameters);
VOID     D3DDevice_GetRasterStatus(__in D3DDevice *pDevice, D3DRASTER_STATUS *pRasterStatus);
VOID     D3DDevice_SetGammaRamp(__in D3DDevice *pDevice, DWORD UnusedFlags, __in CONST D3DGAMMARAMP *pRamp);
VOID     D3DDevice_GetGammaRamp(__in D3DDevice *pDevice, D3DGAMMARAMP *pRamp);
VOID     D3DDevice_SetPWLGamma(__in D3DDevice *pDevice, DWORD Flags, __in CONST D3DPWLGAMMA *pRamp);
VOID     D3DDevice_GetPWLGamma(__in D3DDevice *pDevice, D3DPWLGAMMA *pRamp);
VOID     D3DDevice_SetRenderTarget(__in D3DDevice *pDevice, DWORD RenderTargetIndex, __in_opt D3DSurface *pRenderTarget);
VOID     D3DDevice_SetRenderTarget_External(__in D3DDevice *pDevice, DWORD RenderTargetIndex, __in_opt D3DSurface *pRenderTarget);
VOID     D3DDevice_SetDepthStencilSurface(__in D3DDevice *pDevice, __in_opt D3DSurface *pZStencilSurface);
VOID     D3DDevice_Clear(__in D3DDevice *pDevice, DWORD Count, __in_opt CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, FLOAT Z, DWORD Stencil, BOOL EDRAMClear);
VOID     D3DDevice_ClearF(__in D3DDevice *pDevice, DWORD Flags, __in_opt CONST D3DRECT *pRect, __in_opt CONST D3DVECTOR4* pColor, FLOAT Z, DWORD Stencil);
VOID     D3DDevice_SetViewport(__in D3DDevice *pDevice, __in CONST D3DVIEWPORT9 *pViewport);
VOID     D3DDevice_GetViewport(__in D3DDevice *pDevice, D3DVIEWPORT9 *pViewport);
VOID     D3DDevice_SetRenderState_ParameterCheck(__in D3DDevice *pDevice, D3DRENDERSTATETYPE State, DWORD Value);
VOID     D3DDevice_GetRenderState_ParameterCheck(__in D3DDevice *pDevice, D3DRENDERSTATETYPE State);
VOID     D3DDevice_SetSamplerState_ParameterCheck(__in D3DDevice *pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
VOID     D3DDevice_GetSamplerState_ParameterCheck(__in D3DDevice *pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type);
VOID     D3DDevice_SetTexture(__in D3DDevice *pDevice, DWORD Sampler, __in_opt D3DBaseTexture *pTexture, UINT64 PendingMask3);
VOID     D3DDevice_DrawVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount);
VOID     D3DDevice_DrawIndexedVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount);
VOID     D3DDevice_DrawVerticesUP(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, __in CONST VOID *pVertexStreamZeroData, UINT VertexStreamZeroStride);
VOID     D3DDevice_DrawIndexedVerticesUP(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT IndexCount, __in CONST VOID *pIndexData, D3DFORMAT IndexDataFormat, __in CONST VOID *pVertexStreamZeroData, UINT VertexStreamZeroStride);
VOID     D3DDevice_SetVertexDeclaration(__in D3DDevice* pDevice, __in_opt D3DVertexDeclaration *pDecl);
VOID     D3DDevice_SetScissorRect(__in D3DDevice* pDevice, __in CONST RECT* pRect);
VOID     D3DDevice_GetScissorRect(__in D3DDevice* pDevice, RECT* pRect);
VOID     D3DDevice_SetFVF(__in D3DDevice *pDevice, DWORD FVF);
DWORD    D3DDevice_GetFVF(__in D3DDevice *pDevice);
VOID     D3DDevice_SetVertexShader(__in D3DDevice *pDevice, __in_opt D3DVertexShader *pShader);
VOID     D3DDevice_GetVertexShader(__in D3DDevice *pDevice, __deref_out D3DVertexShader **ppShader);
VOID     D3DDevice_SetVertexShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount);
VOID     D3DDevice_SetVertexShaderConstantFN(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST FLOAT *pConstantData, DWORD Vector4fCount, UINT64 PendingMask0);
VOID     D3DDevice_SetVertexShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4iCount) CONST INT *pConstantData, DWORD Vector4iCount);
VOID     D3DDevice_GetVertexShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount);
VOID     D3DDevice_GetVertexShaderConstantF(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4fCount) FLOAT *pConstantData, DWORD Vector4fCount);
VOID     D3DDevice_GetVertexShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4iCount) INT *pConstantData, DWORD Vector4iCount);
VOID     D3DDevice_SetVertexShaderConstantF_ParameterCheck(__in D3DDevice* pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST FLOAT *pConstantData, DWORD Vector4fCount);
VOID     D3DDevice_SetStreamSource(__in D3DDevice *pDevice, UINT StreamNumber, __in_opt D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride, UINT64 PendingMask3);
VOID     D3DDevice_SetIndices(__in D3DDevice *pDevice, __in_opt D3DIndexBuffer *pIndexData);
VOID     D3DDevice_SetPixelShader(__in D3DDevice *pDevice, __in_opt D3DPixelShader* pShader);
VOID     D3DDevice_GetPixelShader(__in D3DDevice *pDevice, __deref_out D3DPixelShader** ppShader);
VOID     D3DDevice_SetPixelShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount);
VOID     D3DDevice_SetPixelShaderConstantFN(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST FLOAT *pConstantData, DWORD Vector4fCount, UINT64 PendingMask1);
VOID     D3DDevice_SetPixelShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4iCount) CONST INT *pConstantData, DWORD Vector4iCount);
VOID     D3DDevice_GetPixelShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount);
VOID     D3DDevice_GetPixelShaderConstantF(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4fCount) FLOAT *pConstantData, DWORD Vector4fCount);
VOID     D3DDevice_GetPixelShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4iCount) INT *pConstantData, DWORD Vector4iCount);
VOID     D3DDevice_SetPixelShaderConstantF_ParameterCheck(__in D3DDevice* pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST FLOAT *pConstantData, DWORD Vector4fCount);
VOID     D3DDevice_SetClipPlane(__in D3DDevice *pDevice, DWORD Index, __in_ecount(4) CONST FLOAT*  pPlane);
VOID     D3DDevice_GetClipPlane(__in D3DDevice *pDevice, DWORD Index, __out_ecount(4) FLOAT*  pPlane);

VOID     D3DDevice_Resolve(__in D3DDevice* pDevice, DWORD Flags, __in_opt CONST D3DRECT *pSourceRect, __in D3DBaseTexture *pDestTexture, __in_opt CONST D3DPOINT *pDestPoint, UINT DestLevel, UINT DestSliceOrFace, __in_opt CONST D3DVECTOR4* pClearColor, FLOAT ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters);
VOID     D3DDevice_AcquireThreadOwnership(__in D3DDevice* pDevice);
VOID     D3DDevice_ReleaseThreadOwnership(__in D3DDevice* pDevice);
VOID     D3DDevice_SetThreadOwnership(__in D3DDevice* pDevice, DWORD ThreadID);
DWORD    D3DDevice_QueryThreadOwnership(__in D3DDevice* pDevice);
VOID     D3DDevice_Present(__in D3DDevice *pDevice);
BOOL     D3DDevice_IsBusy(__in D3DDevice *pDevice);
VOID     D3DDevice_BlockUntilIdle(__in D3DDevice *pDevice);
VOID     D3DDevice_InsertCallback(__in D3DDevice *pDevice, D3DCALLBACKTYPE Type, __in_opt D3DCALLBACK pCallback, DWORD Context);
VOID     D3DDevice_SetVerticalBlankCallback(__in D3DDevice *pDevice, __in_opt D3DVBLANKCALLBACK pCallback);
VOID     D3DDevice_SetSwapCallback(__in D3DDevice *pDevice, __in D3DSWAPCALLBACK pCallback);
VOID     D3DDevice_SynchronizeToPresentationInterval(__in D3DDevice *pDevice);
VOID     D3DDevice_Swap(__in D3DDevice *pDevice, __in D3DBaseTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters);
VOID     D3DDevice_RenderSystemUI(__in D3DDevice *pDevice);
VOID     D3DDevice_QueryBufferSpace(__in D3DDevice* pDevice, DWORD* pUsed, DWORD* pRemaining);
VOID     D3DDevice_SetPredication(__in D3DDevice* pDevice, DWORD PredicationMask);
VOID     D3DDevice_SetPatchablePredication(__in D3DDevice* pDevice, DWORD PredicationMask, DWORD Identifier);
VOID     D3DDevice_BeginTiling(__in D3DDevice* pDevice, DWORD Flags, DWORD Count, __in_ecount(Count) CONST D3DRECT* pTileRects, __in_opt CONST D3DVECTOR4* pClearColor, FLOAT ClearZ, DWORD ClearStencil);
HRESULT  D3DDevice_EndTiling(__in D3DDevice* pDevice, DWORD ResolveFlags, __in_opt CONST D3DRECT* pResolveRects, __in_opt D3DBaseTexture* pDestTexture, __in_opt CONST D3DVECTOR4* pClearColor, FLOAT ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters);
VOID     D3DDevice_BeginZPass(__in D3DDevice* pDevice, DWORD Flags);
HRESULT  D3DDevice_EndZPass(__in D3DDevice* pDevice);
HRESULT  D3DDevice_InvokeRenderPass(__in D3DDevice* pDevice);
VOID     D3DDevice_BeginExport(__in D3DDevice* pDevice, DWORD Index, __in D3DResource* pResource, DWORD Flags);
VOID     D3DDevice_EndExport(__in D3DDevice* pDevice, DWORD Index, __in D3DResource* pResource, DWORD Flags);
VOID     D3DDevice_DrawTessellatedVertices(__in D3DDevice *pDevice, D3DTESSPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount);
VOID     D3DDevice_DrawIndexedTessellatedVertices(__in D3DDevice *pDevice, D3DTESSPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount);
HRESULT  D3DDevice_SetRingBufferParameters(__in D3DDevice* pDevice, __in_opt CONST D3DRING_BUFFER_PARAMETERS *pParameters);
VOID     D3DDevice_XpsBegin(__in D3DDevice* pDevice, DWORD Flags);
HRESULT  D3DDevice_XpsEnd(__in D3DDevice* pDevice);
VOID     D3DDevice_XpsSetCallback(__in D3DDevice* pDevice, __in D3DXpsCallback pCallback, __in_opt VOID* pContext, DWORD Flags);
VOID     D3DDevice_XpsSubmit(__in D3DDevice* pDevice, DWORD InstanceCount, __in_bcount(Size) CONST VOID* pData, DWORD Size);
VOID     D3DDevice_XpsSetPredication(__in D3DDevice* pDevice, DWORD Predication);
VOID     D3DDevice_XpsSetPredicationFromVisibility(__in D3DDevice* pDevice, HANDLE VisibilityHandle);
VOID     D3DDevice_XpsSetPredicationFromQuery(__in D3DDevice* pDevice, __in_opt IDirect3DQuery9* pQuery);
__out_bcount(VertexCount*VertexStreamZeroStride) VOID*  D3DDevice_BeginVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, UINT VertexStreamZeroStride);
VOID     D3DDevice_EndVertices(__in D3DDevice *pDevice);
HRESULT  D3DDevice_BeginIndexedVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT NumVertices, UINT IndexCount, D3DFORMAT IndexDataFormat, UINT VertexStreamZeroStride, __deref_out VOID** ppIndexData, __deref_out_bcount(NumVertices*VertexStreamZeroStride) VOID** ppVertexData);
VOID     D3DDevice_EndIndexedVertices(__in D3DDevice *pDevice);
DWORD    D3DDevice_InsertFence(__in D3DDevice* pDevice);
VOID     D3DDevice_BlockOnFence(DWORD Fence);
BOOL     D3DDevice_IsFencePending(DWORD Fence);
VOID     D3DDevice_SetBlendState(__in D3DDevice* pDevice, DWORD RenderTargetIndex, D3DBLENDSTATE BlendState);
VOID     D3DDevice_GetBlendState(__in D3DDevice* pDevice, DWORD RenderTargetIndex, D3DBLENDSTATE* pBlendState);
VOID     D3DDevice_SetVertexFetchConstant(__in D3DDevice* pDevice, UINT VertexFetchRegister, __in D3DVertexBuffer* pVertexBuffer, UINT Offset);
VOID     D3DDevice_SetTextureFetchConstant(__in D3DDevice* pDevice, UINT TextureFetchRegister, __in D3DBaseTexture* pTexture);
FLOAT    D3DDevice_GetCounter(__in D3DDevice* pDevice, D3DCOUNTER CounterID);
VOID     D3DDevice_SetSafeLevel(__in D3DDevice* pDevice, DWORD Flags, DWORD Level);
VOID     D3DDevice_GetSafeLevel(__in D3DDevice* pDevice, DWORD* pFlags, DWORD* pLevel);
VOID     D3DDevice_SetHangCallback(__in D3DDevice* pDevice, D3DHANGCALLBACK pCallback);
VOID     D3DDevice_BeginConditionalSurvey(__in D3DDevice* pDevice, DWORD Identifier, DWORD Flags);
VOID     D3DDevice_EndConditionalSurvey(__in D3DDevice* pDevice, DWORD Flags);
VOID     D3DDevice_BeginConditionalRendering(__in D3DDevice* pDevice, DWORD Identifier);
VOID     D3DDevice_EndConditionalRendering(__in D3DDevice* pDevice);
HRESULT  D3DDevice_PersistDisplay(__in D3DDevice* pDevice, __in D3DTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters);
HRESULT  D3DDevice_GetPersistedTexture(__in D3DDevice* pDevice, __deref_out D3DTexture** pFrontBuffer);
VOID     D3DDevice_Suspend(__in D3DDevice* pDevice);
VOID     D3DDevice_Resume(__in D3DDevice* pDevice);
VOID     D3DDevice_EnablePerfCounters(__in D3DDevice* pDevice, BOOL Enable);
VOID     D3DDevice_SetPerfCounterEvents(__in D3DDevice* pDevice, __in CONST D3DPERFCOUNTER_EVENTS* pEvents, DWORD Flags);
VOID     D3DDevice_QueryPerfCounters(__in D3DDevice* pDevice, __in D3DPerfCounters* pCounters, DWORD Flags);
DWORD    D3DDevice_GetNumPasses(__in D3DDevice* pDevice);
VOID     D3DDevice_SetShaderInstructionAllocation(__in D3DDevice* pDevice, DWORD Flags, DWORD VertexShaderBase, DWORD PixelShaderBase);
VOID     D3DDevice_SetShaderGPRAllocation(__in D3DDevice* pDevice, DWORD Flags, DWORD VertexShaderCount, DWORD PixelShaderCount);
VOID     D3DDevice_GetShaderGPRAllocation(__in D3DDevice* pDevice, DWORD* pFlags, DWORD* pVertexShaderCount, DWORD* pPixelShaderCount);
VOID     D3DDevice_SetScreenExtentQueryMode(__in D3DDevice* pDevice, D3DSCREENEXTENTQUERYMODE Mode);
VOID     D3DDevice_GetScreenExtentQueryMode(__in D3DDevice* pDevice, D3DSCREENEXTENTQUERYMODE* pMode);
VOID     D3DDevice_BeginShaderConstantF1_ParameterCheck(__in D3DDevice *pDevice, BOOL PixelShader, UINT StartRegister, DWORD Vector4fCount);
VOID     D3DDevice_EndShaderConstantF1_ParameterCheck(__in D3DDevice *pDevice);
HRESULT  D3DDevice_BeginShaderConstantF4(__in D3DDevice *pDevice, BOOL PixelShader, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, DWORD Vector4fCount);
VOID     D3DDevice_EndShaderConstantF4_ParameterCheck(__in D3DDevice *pDevice);
DWORD    D3DDevice_GetCurrentFence();
VOID     D3DDevice_InvalidateGpuCache(__in D3DDevice* pDevice, __in_bcount(Size) VOID* pBaseAddress, DWORD Size, DWORD Flags);
VOID     D3DDevice_InvalidateResourceGpuCache(__in D3DDevice* pDevice, __in D3DResource* pResource, DWORD Flags);
VOID     D3DDevice_FlushHiZStencil(__in D3DDevice* pDevice, D3DFHZS_FLUSHTYPE FlushType);
VOID     D3DDevice_UnsetAll(__in D3DDevice* pDevice);
DWORD    D3DDevice_GetDeviceState(__in D3DDevice* pDevice);
VOID     D3DDevice_SetBlockCallback(__in D3DDevice* pDevice, DWORD Flags, __in_opt D3DBLOCKCALLBACK pCallback);
VOID     D3DDevice_SetSurfaces(__in D3DDevice* pDevice, __in CONST D3DSURFACES* pSurfaces, DWORD Flags);
VOID     D3DDevice_BeginCommandBuffer(__in D3DDevice* pDevice, __in D3DCommandBuffer* pCommandBuffer, DWORD Flags, __in_opt CONST D3DTAGCOLLECTION* pInheritTags, __in_opt CONST D3DTAGCOLLECTION* pPersistTags, __in_opt CONST D3DRECT* pTilingRects, DWORD TileCount);
HRESULT  D3DDevice_EndCommandBuffer(__in D3DDevice* pDevice);
VOID     D3DDevice_RunCommandBuffer(__in D3DDevice* pDevice, __in D3DCommandBuffer* pD3dCommandBuffer, DWORD PredicationSelect);
HRESULT  D3DDevice_InsertAsyncCommandBufferCall(__in D3DDevice* pDevice, __in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, DWORD PredicationSelect, DWORD Flags);
VOID     D3DDevice_SetCommandBufferPredication(__in D3DDevice* pDevice, DWORD TilePredication, DWORD RunPredication);
DWORD    D3DDevice_InsertMarker(__in D3DDevice* pDevice);
VOID     D3DDevice_Nop(__in D3DDevice* pDevice, DWORD Count);
VOID     D3DDevice_QuerySwapStatus(__in D3DDevice* pDevice, D3DSWAP_STATUS* pSwapStatus);
DWORD    D3DDevice_PixBeginNamedEvent(__in D3DDevice *pDevice, DWORD Color, __in_z CONST char *szName, va_list Arglist);
DWORD    D3DDevice_PixEndNamedEvent(__in D3DDevice *pDevice);
VOID     D3DDevice_PixSetMarker(__in D3DDevice *pDevice, DWORD Color, __in_z CONST char *szName, va_list Arglist);
VOID     D3DDevice_PixIgnoreTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture);
VOID     D3DDevice_PixStopIgnoringTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture);
VOID     D3DDevice_PixIgnoreMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const VOID* pBaseAddress, DWORD Size);
VOID     D3DDevice_PixStopIgnoringMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const VOID* pBaseAddress, DWORD Size);
HRESULT  D3DDevice_PixSetTextureName(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture, __in_z const char* pName);
VOID     D3DDevice_PixReportNewTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture);
VOID     D3DDevice_PixReportDeletedTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture, BOOL BaseDeleted, BOOL MipDeleted);
VOID     D3DDevice_PixReportMovedMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const VOID* pDestinationAddress, __in_bcount(Size) const VOID* pSourceAddress, DWORD Size);
VOID     D3DDevice_PixReportFreedMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const VOID* pAddress, DWORD Size);

VOID     D3DDevice_SetViewportF(__in D3DDevice *pDevice, __in CONST D3DVIEWPORTF9* pViewportF);
VOID     D3DDevice_GetViewportF(__in D3DDevice *pDevice, D3DVIEWPORTF9* pViewportF);
HANDLE   D3DDevice_BeginVisibilitySurvey(__in D3DDevice* pDevice, DWORD Flags);
VOID     D3DDevice_EndVisibilitySurvey(__in D3DDevice* pDevice, HANDLE VisibilityHandle);
VOID     D3DDevice_SetSwapMode(__in D3DDevice* pDevice, BOOL Asynchronous);
D3DASYNCBLOCK  D3DDevice_InsertBlockOnAsyncResources(__in D3DDevice* pDevice, DWORD WriteCount, __in_ecount_opt(WriteCount) D3DResource* CONST* pWriteResourceList, DWORD ReadCount, __in_ecount_opt(ReadCount) D3DResource* CONST* pReadResourceList, DWORD Flags);
VOID     D3DDevice_SignalAsyncResources(__in D3DDevice* pDevice, D3DASYNCBLOCK AsyncBlock);
D3DAsyncCommandBufferCall*  D3DDevice_CreateAsyncCommandBufferCall(__in D3DDevice* pDevice, __in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags);

}