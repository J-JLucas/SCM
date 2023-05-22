// Fill out your copyright notice in the Description page of Project Settings.


#include "SCM_PlayerHUD.h"
#include "Engine/Canvas.h"

void ASCM_PlayerHUD::DrawHUD()
{
    Super::DrawHUD();
    // Draw Crosshair

    if (CrosshairTexture)
    {
        // Find the center of our canvas.
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // Draw the crosshair at the centerpoint.
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}
