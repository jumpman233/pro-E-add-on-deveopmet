(Dialog subgrid
(Components
(PushButton OK)
(PushButton Cancel)
(InputPanel FeatNamePanel)
(Label FeatNameLabel)
)
(Resources
(OK.Label "OK")
(OK.TopOffset 4)
(OK.BottomOffset 4)
(OK.LeftOffset 4)
(OK.RightOffset 4)
(Cancel.Label "Cancel")
(Cancel.TopOffset 4)
(Cancel.BottomOffset 4)
(Cancel.LeftOffset 4)
(Cancel.RightOffset 4)
(FeatNamePanel.TopOffset 4)
(FeatNamePanel.BottomOffset 4)
(FeatNamePanel.LeftOffset 4)
(FeatNamePanel.RightOffset 4)
(FeatNameLabel.Label "Feature name")
(.Label "Subgrid")
(.Layout
(Grid (Rows 1 1 1) (Cols 1)
FeatNameLabel
FeatNamePanel
(Grid (Rows 1) (Cols 1 1)
OK
Cancel
)
)
)
)