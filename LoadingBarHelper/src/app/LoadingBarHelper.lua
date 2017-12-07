loadingBarHelper = {}

local StartEnum ={
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4,
}

local Direction = {
	HORIZONTAL = 1,
	VERTICAL = 2,
}

-- 创建Bar进度条ProgressTimer
function loadingBarHelper.createProgressBar(spriteFileName,anchorPoint,scaleX,scaleY,positionX,positionY,start,direction,percent)
    local midpoint = nil
    if start == StartEnum.LEFT then    
        midpoint = cc.p(0,0.5) -- 起始点在左
    elseif start == StartEnum.RIGHT then 
        midpoint = cc.p(1,0.5) -- 起始点在右
    elseif start == StartEnum.UP then 
        midpoint = cc.p(0.5,1) -- 起始点在上
    elseif start == StartEnum.DOWN then 
        midpoint = cc.p(0.5,0) --起始点在下
    end 
    local changeRate = ifReturn((direction==Direction.HORIZONTAL),cc.p(1,0),cc.p(0,1))  -- 1为水平  2 为竖直

    local ct = cc.ProgressTimer:create(cc.Sprite:create(spriteFileName))
    ct:setType(kCCProgressTimerTypeBar)
    ct:setAnchorPoint(anchorPoint)
    ct:setScaleX(scaleX)
    ct:setScaleY(scaleY)
    ct:setPosition(cc.p(positionX,positionY))
    ct:setMidpoint(midpoint) --设置起始点
    ct:setBarChangeRate(changeRate)     --设置起始方向 
    ct:setPercentage(100 * percent) --设置起始百分比
    return ct
end

-- 创建环形进度条ProgressTimer
function loadingBarHelper.createProgressRadial( spriteFileName,anchorPoint,positionX,positionY,percent,isReverse,midpoint )
    local ct = cc.ProgressTimer:create(cc.Sprite:create(spriteFileName))
    ct:setType(kCCProgressTimerTypeRadial)
    ct:setReverseProgress(isReverse)  --是否可逆
    ct:setAnchorPoint(anchorPoint)
    ct:setPosition(cc.p(positionX,positionY))
    ct:setPercentage(percent)
    ct:setMidpoint(midpoint)
    return ct
end

return loadingBarHelper